
/* This is the source code for S-PHXKS (Steel's Performance Hybrid Crossover Kernel System) kernel.
It is an ACTUAL kernel, unlike that of Steel OS, which was Steel32 and Steel64.

It's also the NanamiOS kernel.

Feel free to use it (along with other provided stuff) to make your own clone or OS based off of the
S-PHXKS kernel, it's open source and who knows, if I play things out right, could be something just as
good and capable as Linux!*/

#include "types.h"
#include "gdt.h"
#include "interrupts.h"
#include "keyboard.h"
#include "mouse.h"


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
      y++;
      x = 0;
    }

    if(y >= 25)
    {
      for(y = 0; y < 25; y++)
        for(x = 0; x < 80; x++)
          VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' '; // Video memory!! Immediately in the kernel! Yayyy! ^_^

      x = 0;
      y=0;
    }
  }
}



extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
  // Version headers have to be replaced manually. This hopefully shouldn't be too much!
  printf("                ----- NanamiOS 1.00.18[Codename \"Reimu\"] -----                \n --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid\n\nKernel: S-PHXKS - Build Date: 2023 October 31st\n\n[Caution!] Use this build at your risk. I haven't developed a lot of drivers or a command line yet, so it doesn't do much. Sorry! >_<\n[Caution!] In order to power NanamiOS off, you need to press the power button. You can't hit CTRL+ALT+DEL!!");
  printf("\n\nFor assistance, contact steelsofliquid@hotmail.com between 8 AM and 7 PM Eastern US & Canada Time.\n");
  printf("[Warning] Testing is being done on the OS in this build involving potentially unstable stuff. Proceed with caution!");

  // ^- The boot message ^_^
  // Build 16 on 2023 October 31st: I updated the message and as of now, this build is dated on Halloween. OoOoOoO sPoOkY!!!!
  // Mehh... Perhaps I should cosplay the nime girl I named the OS after next year on Halloween... (That would be Nanami Madobe).
  // I already resemble her enough!

  GlobalDescriptorTable gdt;
  printf("\n[Ready!] NanamiOS Global Descriptor Table");
  InterruptManager interrupts(&gdt);
  printf("\n[Ready!] NanamiOS Interrupt Manager");

  // ^- The background processes being loaded in

  KeyboardDriver keyboard(&interrupts);
  printf("\n[Ready!] NanamiOS \"NanamiKeyboard\" Keyboard Driver"); // Oopsies! I forgot a semicolon! >_<
  MouseDriver mouse(&interrupts);
  printf("\n[Ready!] NanamiOS \"NanamiMouse\" Mouse Driver");

  // ^- The drivers being loaded in

  /* I put these here on purpose to do do a time test of how the OS loads its services, the two current ones
  only being the global descriptor table and interrupt manager. they should load instantly, but who know what
  will happen if you're using an i386 or i486. ^_^ 
  
  [Heck, does NanamiOS even work on a 486...?]>- (¬.¬)*/

  interrupts.Activate(); // This hopefully shouldn't perform a triple fault ^.^
  // it didn't! ^_^

  // ^- Region of 11B-Present interrupts

  while(1); // Nothing happens! ...For now.
  
}

