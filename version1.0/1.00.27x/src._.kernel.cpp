
/* This is the source code for S-PHXKS (Steel's Performance Hybrid Crossover Kernel System) kernel.
It is an ACTUAL kernel, unlike that of Steel OS, which was Steel32 and Steel64.

It's also the NanamiOS kernel.

Feel free to use it (along with other provided stuff) to make your own clone or OS based off of the
S-PHXKS kernel, it's open source and who knows, if I play things out right, could be something just as
good and capable as Linux!*/

#include "include.common.types.h"
#include "include._.gdt.h"
#include "include.hwcom.interrupts.h"
#include "include.hwcom.pci.h"
#include "include.drivers.driver.h"
#include "include.drivers.keyboard.h"
#include "include.drivers.mouse.h"


void printf(char* str)
{
  static uint16_t* VideoMemory = (uint16_t*)0xb8000; // The video memory is the same for all GPUs for now. It doesn't matter if your PC has a flashy brand-new RTX or an ancient Voodoo. NanamiOS treats both cards equally.
  
  static uint8_t x =0 , y=0;

  for(int i = 0; str[i] != '\0'; ++i)
  {

    switch(str[i])
    {

      case '\n': // Line-breaker! ^_^
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

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
  for(constructor* i = &start_ctors; i != &end_ctors; i++)
    (*i)();
}

// ^- This is experimental. I'm adding this back (as I archived it from the garbage code), but with a
// slight change. I wonder if this change is a bug...

// The original one was missing an "&" and this caused an error preventing the code from compiling.
// That was back before NanamiOS 1.00 Build 1, however...

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
  // Version headers have to be replaced manually. This hopefully shouldn't be too much!
  printf("SteelsOfLiquid NanamiOS [NanamiMadobe OS Version 1.00.27 Codename \"Reimu\" Alpha]\n");
  // Decided to shorten this from 86 to 80 characters. It just seems like it'd be weird for this line to go past the first one.

  GlobalDescriptorTable gdt; // background processes
  printf("[Ready!] NanamiOS Global Descriptor Table\n");
  InterruptManager interrupts(&gdt);
  printf("[Ready!] NanamiOS Interrupt Manager\n");

  DriverManager drvManager;
    printf("[Ready!] NanamiOS Driver Manager\n");

    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&interrupts, &kbhandler); // Oopsies! I forgot a semicolon! >_< (a bit back)
    drvManager.AddDriver(&keyboard);
    printf("[Ready!] NanamiKeyboard - NanamiOS Keyboard Driver\n");

    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler); // drivers loading
    drvManager.AddDriver(&mouse);
    printf("[Ready!] NanamiMouse - NanamiOS Mouse Driver\n"); // Oops... I did it again... * tapping chin/mouth *
    // That comment was a reference to the Windows 7 anime commercial, where Nanami Madobe forgot a screw in the PC
    // she built, causing the front panel to fall forward onto her desk. Do I know what she actually said there? No.
    // Do I have an idea of what she said? Maybe. I forgot a semi-colon here...

    PCIController PCIController;
    PCIController.SelectDrivers(&drvManager, &interrupts);

    printf("[Ready!] NanamiPCI\n");

    drvManager.ActivateAll();
  
  printf("[Online] NanamiOS System Drivers\n");

  /* I put these here on purpose to do do a time test of how the OS loads its services, the two current ones
  only being the global descriptor table and interrupt manager. they should load instantly, but who know what
  will happen if you're using an i386 or i486. ^_^ 

  [Heck, does NanamiOS even work on a 486...?]>- (¬.¬)*/

  interrupts.Activate(); // This hopefully shouldn't perform a triple fault ^.^
  // it didn't! ^_^ ...At least with the GDT set the way it is.
  printf("[Online] NanamiOS Interrupts System\n");

  // ^- Interrupts being loaded

  // This portion of "printf("\n")" will try to clear the screen to make the splash appear.
  // The question is, HOW many lines do I need to print?

/*
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");

*/

  // Remove the comment pins to activate more of a technical mode.

  // Splooosh!!!

  /*  

  printf(" Version 1.00.27A EnUS \"Reimu\" /                 / F4 = Help / NanamiOS S-PHXKS ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf("        -           -            ----                            --- ---        ");
  printf("       ---  --     ---  --          -          --   --          -   -   -       ");
  printf("        -     -     -     -      ----  -      -  - -             -     -        ");
  printf("        -   -       -   -       -  - ---      -  -  --            -   -         ");
  printf("        -  ---      -  ---      - -   -       -  -    -         |  - -  |       ");
  printf("       -   -- -    -   -- -      --  -         --   --          |   -   |       ");
  printf("                                                                 _______/       ");
  printf("                        L                                                       ");
  printf("        A                               P                               A       ");
  printf("                                                        H                       ");
  printf("                                                                                ");
  printf("                                                                                ");  // Reminds me of Wii channels!
  printf("                                                                                ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf("                                                                                ");
  printf(" Created with moe skills by SteelsOfLiquid <3   /   Press any key to dismiss  /");

  */

  // This section is comment pin capable.

  // ^- The boot message ^_^
  // Build 16 on 2023 October 31st: I updated the message and as of now, this build is dated on Halloween. OoOoOoO sPoOkY!!!!
  // Build 20 on 2023 November 1st: If you want to talk spooky, the OS had some glitches.
  // Mehh... Perhaps I should cosplay the anime girl I named the OS after next year on Halloween... (That would be Nanami Madobe).
  // I already resemble her enough!

  /* Build 20: I replaced the much more technical boot message with a much "simpler" boot screen. Though it looks simple, it's
  not - I had to inject ASCII art into the OS that was compatible with an original 80x24 text set. This meant I had to add 24 printf
  lines, and, given prior to this, I've have never made ASCII art, I had to figure out how to make ASCII art. So, I did some ASCII
  art of the Japanese hiragana for "Nanami" (as this is designed for a i386 IBM PC-compatible system, it doesn't have any Japanese
  text characters in the BIOS font compared to things like PC-98 and modern Japanese computers), I also did ASCII art of an enlarged
  text of "OS", a PC resembling something you'd see in the ad and wallpapers starring Nanami Madobe (fun fact, she didn't put RGB in
  her computers, or at least the ones she's seen building, I also generally don't see why RGB is needed, but if you're like me and
  leave your PC on it does make a good night light), some borders, and the four-leaf clover badge seen on Nanami's hair clip. I also
  stretched out the word "Alpha" to indicate this is an alpha release. I would've done ASCII art of Nanami herself, but this build has
  been lagging on a little bit, given I needed to quickly rush to try and patch bugs in the drivers (the shift key stayed on after you
  pressed it once, and the mouse would overwrite text positions in a trail-style), and finish the build. */

  /* Build 26 on 2023 November 5th: 
  So, I made the boot screen more in-line with "industry standards". This means that I removed the ASCII art of a PC and the badge seen on
  Nanami's hair clip, though I reworked the ASCII art of the hiragana for "Nanami", centered it (and the text saying "OS"), and changed
  the main screen display borders so the top mirrors the bottom. The ASCII art at the bottom is supposed to be a heart making ripples in
  water, but I kinda suck at ASCII art, and needed to create this ASCII boot screen inside of the editor (it's hard-coded) to actually
  get the proper idea of what I wanted the image to look like. */

  /* Build 26 on 2023 November 6th:
  Yeah, you can kinda see how long it took me to develop this build. It has to do with the PCI development!! */

  /* Build 26 on 2023 November 6th:
  I moved this entire block to be placed after everything's loaded. This lets us see if something has gone wrong during
  startup! ^_^ */

  /* Build 26 on 2023 November 7th:
  Once again, another day on the development of this build! For reference, I've been working on this build since the 3rd! */

  /* Build 27 on 2023 November 9th:
  Use Visual Studio Code or other similar program/font with a font displaying each text character of equal length. The ASCII art
  won't render right otherwise! */

  /* Build 27 on 2023 November 16th:
  So, I decided to just have the Japanese text, "Alpha" in the shape of a wave, etc. */

  while(1); // Nothing happens! ...For now.
  
}

