
void printf(char* str)
{
  unsigned short* VideoMemory = (unsigned short*)0xb8000;
  
  for(int i = 0; str[i] != '\0'; ++i)
    VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
  
}



extern "C" void kernelMain(void* multiboot_structure, unsigned int magicnumber)
{
  printf("NanamiOS 1.00.1 [Codename Kitsune] --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid");
  
  while(1);
  
}

