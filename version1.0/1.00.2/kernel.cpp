
void printf(char* str)
{
  unsigned short* VideoMemory = (unsigned short*)0xb8000;
  
  for(int i = 0; str[i] != '\0'; ++i)
    VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
  
}



extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
  printf("----- NanamiOS 1.00.2 [Codename \"Reimu\"] -----\n --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid]\n\n[Caution!] Use this build at your risk. I haven't developed drivers or a command line yet, so it basically does nothing. Sorry! >_<");
  
  while(1);
  
}

