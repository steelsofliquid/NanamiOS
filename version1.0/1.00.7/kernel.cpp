
/* This is the source code for S-PHXKS (Steel's Performance Hybrid Crossover Kernel System) kernel.
It is an ACTUAL kernel, unlike that of Steel OS, which was Steel32 and Steel64.

Feel free to use it (along with other provided stuff) to make your own clone or OS based off of the
S-PHXKS kernel, it's open source and who knows, if I play things out right, could be something just as
good and capable as Linux!*/

#include "types.h"
#include "gdt.h"
#include "interrupts.h"


void printf(char* str)
{
  static uint16_t* VideoMemory = (uint16_t*)0xb8000; // The video memory is the same for all GPUs for now. It doesn't matter if your PC has a flashy brand-new RTX or an ancient Voodoo. NanamiOS treats both cards equally.
  
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
        VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
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
          VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';

      x = 0;
      y=0;
    }
  }
}



extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
  printf("                ----- NanamiOS 1.00.7 [Codename \"Reimu\"] -----                \n --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid]\n\nKernel: S-PHXKS - Build Date: 2023 October 28th\n\n[Caution!] Use this build at your risk. I haven't developed drivers or a command line yet, so it basically does nothing. Sorry! >_<\n[Caution!] In order to power NanamiOS off, you need to press the power button. You can't hit CTRL+ALT+DEL!!");
  printf("\n\nFor assistance, contact steelsofliquid@hotmail.com between 8 AM and 7 PM Eastern US & Canada Time.\n\n[Caution!] The system may be prone to a triple fault (Guru meditation in VirtualBox).");

  GlobalDescriptorTable gdt;
  InterruptManager interrupts(&gdt);

  // interrupts.Activate(); 
  // will it perform tiple fault if i turn the interrupts activate into a comment
  // POST-ISO DEV NOTE (1.00 BUILD 5 2023 OCT. 28TH) - A TRIPLE FAULT EXCEPTION IS PRESENT. I DON'T KNOW HOW I DID IT, BUT IT PREVENTS THE OS FROM WORKING.

  while(1); // Nothing happens! ...For now.
  
}

