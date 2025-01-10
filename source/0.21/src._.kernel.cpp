#include "include.common.types.h"
#include "include._.gdt.h"
#include "include.hwcom.interrupts.h"
#include "include.hwcom.pci.h"
#include "include.drivers.driver.h"
#include "include.drivers.keyboard.h"
#include "include.drivers.mouse.h"
#include "include.drivers.pit.h"
#include "include.drivers.speaker.h"
#include "include.drivers.vga.h"
#include "include._.multitasking.h"

void printf(char* str)
{
  static uint16_t* VideoMemory = (uint16_t*)0xb8000;
  
  static uint8_t x =0 , y=0;

  for(int i = 0; str[i] != '\0'; ++i)
  {

    switch(str[i])
    {

      case '\n':
        y++;
        x = 0;
        break;

      default:
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i]; // And, now, for a more serious comment, this system takes the current line, and moves the text """""placer""""" until it's at a new line.
        x++;
        break;
    }

    if(x >= 80)
    {
      x = 0;
      y++;
    }

    if(y >= 25)
    {
      for(y = 0; y < 25; y++)
        for(x = 0; x < 80; x++)
          VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' '; // Video memory!! Immediately in the kernel! Yayyy! ^_^

      x = 0;
      y = 0;
    }
  }
}

void sleep(uint32_t interval)
{
  // Code in this thing is based off of the equivalent in osakaOS.
  // If interval = 1, that is 1 ms. Probably.

  ProgrammableIntervalTimer ProgrammableIntervalTimer;

  for (uint32_t i = 0; i < interval; i++)
  {
    ProgrammableIntervalTimer.SetPITCount(1193182 / 1000);
    uint32_t timing = ProgrammableIntervalTimer.ReadPIT();

    while ((timing - ProgrammableIntervalTimer.ReadPIT()) < 1000)
    {
    }
  }
}

void printfHex(uint8_t key)
{
  char* foo = "00";
  char* hex = "0123456789ABCDEF";
  foo[0] = hex[(key >> 4) & 0xF];
  foo[1] = hex[key & 0xF];
  printf(foo);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
  void OnKeyDown(char c)
  {
    char* foo = " ";
    foo[0] = c;
    printf(foo);
  }

};

class MouseToConsole : public MouseEventHandler
{
  int8_t x, y;
public:
  MouseToConsole()
  {
    uint16_t* VideoMemory = (uint16_t*)0xB8000;
    x = 40;
    y = 12;
    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                        | (VideoMemory[80*y+x] & 0xF000) >> 4
                        | (VideoMemory[80*y+x] & 0x00FF);
  }

  void OnMouseMove(int xoffset, int yoffset)
  {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000; // The video memory is the same for all GPUs for now. It doesn't matter if your PC has a flashy brand-new RTX or an ancient Voodoo. NanamiOS treats both cards equally.

    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                        | (VideoMemory[80*y+x] & 0xF000) >> 4
                        | (VideoMemory[80*y+x] & 0x00FF);

    x += xoffset;
    if(x < 0) x = 0;
    if(x >= 80) x = 79;

    y += yoffset; // Can we patch an inverted y-axis with minimal code?
    if(y < 0) y = 0;
    if(y >= 25) y = 24;

    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                        | (VideoMemory[80*y+x] & 0xF000) >> 4
                        | (VideoMemory[80*y+x] & 0x00FF);
  }

};

void TestTask1()
{
  while(true)
    printf("[i] This is a testing task. It will display this message continously. (TestTask1");
}

void TestTask2()
{
  while(true)
    printf("[i] This is a testing task. It will display this message continously. (TestTask2");
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++)
    (*i)();
}

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{

  /* r_nanamitsukasa at 13:08 toronto on 2024 july 2:
  I'm going to try something new, that being to add a number of printf things at the top to refresh the screen.*/

  // printf("                                                                                ");

  // Version headers have to be replaced manually. This hopefully shouldn't be too much!
  printf("\n\\\\ SteelsOfLiquid Nanami/OS version 0.21.34 \"Reimu\"\n");
  printf("  By SteelsOfLiquid, based on WYOOS. Licensed under GNU-GPL 3.0\n");
  printf("  For assistance, contact steelsofliquid@hotmail.com\n\n");

  GlobalDescriptorTable gdt;

  TaskManager taskManager;
  Task task1(&gdt, TestTask1);
  Task task2(&gdt, TestTask2);
  // taskManager.AddTask(&task1);
  // taskManager.AddTask(&task2);

  InterruptManager interrupts(0x20, &gdt, &taskManager);

  DriverManager drvManager;
    printf("Starting Drivers...\n");

    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&interrupts, &kbhandler); // Oopsies! I forgot a semicolon! >_< (a bit back)
    drvManager.AddDriver(&keyboard);

    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler); // drivers loading
    drvManager.AddDriver(&mouse);
    // printf("[DRV] Mouse Driver  "); // Oops... I did it again... * tapping chin/mouth *
    // That comment was a reference to the Windows 7 anime commercial, where Nanami Madobe forgot a screw in the PC
    // she built, causing the front panel to fall forward onto her desk. Do I know what she actually said there? No.
    // Do I have an idea of what she said? Maybe. I forgot a semi-colon here...

    // gotta keep that one in here

    Speaker speaker;

    printf("Drivers Started!\n");

    PCIController PCIController;
    printf("Selecting PCI Drivers...\n");
    PCIController.SelectDrivers(&drvManager, &interrupts);

    // VideoGraphicsArray vga;

    drvManager.ActivateAll();

  interrupts.Activate();

  sleep(1);
  speaker.beep();
  printf("System Online! Strike [F1] for help.\n");
  /* vga.SetMode(320, 200, 8);
  for(int32_t y = 0; y < 200; y++)
    for(int32_t x = 0; x < 320; x++)
      vga.PutPixel(x, y, 0x00, 0x00, 0xA8);
    */
  // Splooosh!!!

  /*

  printf(" Nanami/OS Version 0.21.31B EnUS Codename \"Reimu\" (Alpha)          Kon'nichiwa! ");
  printf("                                     ╔════╗                                     ");
  printf("                                     ║    ╠═════╗              ░░░░ ░░          ");
  printf("                                     ║    ║     ║             ░░   ░░           ");
  printf("                          ╔══════════╣    ║     ║            ░░    ░░           ");
  printf("                          ║          ║    ║     ║            ░░    ░░           ");
  printf("                          ║          ╚═╦══      ║             ░░                ");
  printf("        █           █            ████  ║   █                     ▄▄▄ ▄▄▄        ");
  printf("       ███  ██     ███  ██          █      █   ██   ██          █   █   █       ");
  printf("        █     █     █     █      ████  █  █   █  █ █             █     █        ");
  printf("        █   █       █   █       █  █ ███  █   █  █  ██            █   █         ");
  printf("        █  █ █      █  █ █      █ █   █  █    █  █    █         █  █ █  █       ");
  printf("       █   ██ █    █   ██ █      ██  █   █     ██   ██          █   █   █       ");
  printf("                                       ║                         ▄▄▄▄▄▄▄        "); // α not to be confused with a. This is a boot splash and uses α to indicate "alpha".
  printf("                        L              ║                                        ");
  printf("        A                 ║             P                               A       ");
  printf("══╗                       ║            ║                H                       ");
  printf("  ║                       ╚══════╦══╦══╝                                        ");
  printf("  ║                              ║  ║                                           ");  // Reminds me of Wii channels!
  printf("  ║                              ║  ║                                           ");
  printf("══╝                              ╚══╝                                           ");
  printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒░░░░░░░░░░░");
  printf("                  Created with moe skills by SteelsOfLiquid ♥                  ");

  */

  // This section is comment pin capable.

  /* Build 29 on 2023 November 27th:
  I have added cooler Code Page 437 art (Code Page 437 is the BIOS font and character set, aka Extended ASCII)
  to the boot screen.
  
  Build 33 on 2024 November 3rd:
  Don't use it, it'll break the text mode graphics!!!*/

  while(1); // Nothing happens! ...For now.
  
}

