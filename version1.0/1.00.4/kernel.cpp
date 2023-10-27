
#include "types.h"
#include "gdt.h"


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
  printf("                ----- NanamiOS 1.00.4 [Codename \"Reimu\"] -----                \n --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid]\n\nKernel: S-PHXKS - Build Date: 2023 October 27th - Features: GDT, Ports, Boot, & TextDisplay\n\n[Caution!] Use this build at your risk. I haven't developed drivers or a command line yet, so it basically does nothing. Sorry! >_<\n[Caution!] In order to power NanamiOS off, you need to press the power button. You can't hit CTRL+ALT+DEL!!");
  printf("\n\nFor assistance, contact steelsofliquid@hotmail.com between 8 AM and 7 PM Eastern US & Canada Time.");

  GlobalDescriptorTable gdt;

  while(1);
  
}

