
/* This is the source code for S-PHXKS (Steel's Performance Hybrid Crossover Kernel System) kernel.
It is an ACTUAL kernel, unlike that of Steel OS, which was Steel32 and Steel64.

It's also the NanamiOS kernel.

Feel free to use it (along with other provided stuff) to make your own clone or OS based off of the
S-PHXKS kernel, it's open source and who knows, if I play things out right, could be something just as
good and capable as Linux!*/

#include "include.common.types.h"
#include "include._.gdt.h"
#include "include.hwcom.interrupts.h"
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
  }

  void OnMouseMove(int xoffset, int yoffset)
  {
    static uint16_t* VideoMemory = (uint16_t*)0xb8000; // The video memory is the same for all GPUs for now. It doesn't matter if your PC has a flashy brand-new RTX or an ancient Voodoo. NanamiOS treats both cards equally.

    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) >> 4
                        | (VideoMemory[80*y+x] & 0xF000) << 4
                        | (VideoMemory[80*y+x] & 0x00FF);

    x += xoffset;
    if(x < 0) x = 0;
    if(x >= 80) x = 79;

    y -= yoffset;
    if(y < 0) y = 0;
    if(y >= 25) y = 24;

    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) >> 4
                        | (VideoMemory[80*y+x] & 0xF000) << 4
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

extern "C" void kernelMain(void* multiboot_structure, uint32_t magicnumber)
{
  // Version headers have to be replaced manually. This hopefully shouldn't be too much!
  printf("                 ----- NanamiOS 1.00.23[Codename \"Reimu\"] -----                 ");
  printf(" Platform     Version    Kernel     Build Date          |       Genuine      / |");
  printf(" NanamiOS     1.00.23    S-PHXKS    2023 Nov. 2         | copy of NanamiOS  v  |");
  printf("   -- Strike F4 for help! --                            +----------------------+");
  printf("_______________________________________________________________________________/");
  printf("                                                                 -- --          ");
  printf("              -           -            ----        [Nanami]     -- - --         ");
  printf("             ---  --     ---  --          -         --   --    -  - -  -        ");
  printf("              -     -     -     -      ----  -     -  - -       -  -  -         ");
  printf("              -   -       -   -       -  - ---     -  -  --    -  - -  -        ");
  printf("              -  ---      -  ---      - -   -      -  -    -    -- - --         ");
  printf("             -   -- -    -   -- -      --  -        --   --      -- --          ");
  printf("                                           Version 1.00                         ");
  printf("        A               L               P               H               A       ");
  printf("                                                                                ");
  printf("                 ---------                                                      ");
  printf("                 -       -                                                      ");
  printf("                 -       -      -------                                         ");
  printf("                 -       -      - ___ -                                         ");
  printf("                 ---------      -     -                                         ");
  printf("                     -          -  .  -                                         ");
  printf("                  -------        -----                                          ");
  printf("                                                                                ");
  printf("\\______________________________________________________________________________/");
  printf(" Created with moe skills by SteelsOfLiquid <3    -- Press any key to dismiss --");

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

  GlobalDescriptorTable gdt; // background processes
  InterruptManager interrupts(&gdt);

  DriverManager drvManager;

    PrintfKeyboardEventHandler kbhandler;
    KeyboardDriver keyboard(&interrupts, &kbhandler); // Oopsies! I forgot a semicolon! >_< (a bit back)
    drvManager.AddDriver(&keyboard);

    MouseToConsole mousehandler;
    MouseDriver mouse(&interrupts, &mousehandler); // drivers loading
    drvManager.AddDriver(&mouse);

    drvManager.ActivateAll();

  /* I put these here on purpose to do do a time test of how the OS loads its services, the two current ones
  only being the global descriptor table and interrupt manager. they should load instantly, but who know what
  will happen if you're using an i386 or i486. ^_^ 
  // I removed those

  [Heck, does NanamiOS even work on a 486...?]>- (¬.¬)*/

  interrupts.Activate(); // This hopefully shouldn't perform a triple fault ^.^
  // it didn't! ^_^

  // ^- Interrupts being loaded

  while(1); // Nothing happens! ...For now.
  
}

