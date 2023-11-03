// My first driver! ^_^

#include "keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(0x21, manager),
dataport(0x60),
commandport(0x64)
{
    //
}

KeyboardDriver::~KeyboardDriver()
{
    //
}

void KeyboardDriver::Activate()
{
    while(commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xAE); // Activate interrupts
    commandport.Write(0x20); // Get current state
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // Set the state
    dataport.Write(status);

    dataport.Write(0xF4);
}

void printf(char*);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    static bool Shift = false;

        switch(key)
        {
            case 0xFA: break;

            case 0x29: if(Shift) printf("~"); else printf("`"); break;
            case 0x02: if(Shift) printf("!"); else printf("1"); break;
            case 0x03: if(Shift) printf("@"); else printf("2"); break;
            case 0x04: if(Shift) printf("#"); else printf("3"); break;
            case 0x05: if(Shift) printf("$"); else printf("4"); break;
            case 0x06: if(Shift) printf("%"); else printf("5"); break;
            case 0x07: if(Shift) printf("^"); else printf("6"); break;
            case 0x08: if(Shift) printf("&"); else printf("7"); break;
            case 0x09: if(Shift) printf("*"); else printf("8"); break;
            case 0x0A: if(Shift) printf("("); else printf("9"); break;
            case 0x0B: if(Shift) printf(")"); else printf("0"); break;
            case 0x0C: if(Shift) printf("_"); else printf("-"); break;
            case 0x0D: if(Shift) printf("+"); else printf("="); break;

            case 0x0F: printf("     "); break; // Tab key
            case 0x10: if(Shift) printf("Q"); else printf("q"); break;
            case 0x11: if(Shift) printf("W"); else printf("w"); break;
            case 0x12: if(Shift) printf("E"); else printf("e"); break;
            case 0x13: if(Shift) printf("R"); else printf("r"); break;
            case 0x14: if(Shift) printf("T"); else printf("t"); break;
            case 0x15: if(Shift) printf("Y"); else printf("y"); break;
            case 0x16: if(Shift) printf("U"); else printf("u"); break;
            case 0x17: if(Shift) printf("I"); else printf("i"); break;
            case 0x18: if(Shift) printf("O"); else printf("o"); break;
            case 0x19: if(Shift) printf("P"); else printf("p"); break;
            case 0x1A: if(Shift) printf("{"); else printf("["); break;
            case 0x1B: if(Shift) printf("}"); else printf("]"); break;
            case 0x2B: if(Shift) printf("|"); else printf("\\"); break; // A second backslash is deployed, because purely one backslah will just break the code.

            case 0x1E: if(Shift) printf("A"); else printf("a"); break; // Original code stated "this key (a) is assigned to hex 0x1E". I watched the video, and it turns out, that's the A key! So, that's a start!
            case 0x1F: if(Shift) printf("S"); else printf("s"); break;
            case 0x20: if(Shift) printf("D"); else printf("d"); break;
            case 0x21: if(Shift) printf("F"); else printf("f"); break;
            case 0x22: if(Shift) printf("G"); else printf("g"); break;
            case 0x23: if(Shift) printf("H"); else printf("h"); break;
            // case 0x17: printf("I"); break; NOT SUPPOSED TO BE IN THIS ROW!!! >_<
            case 0x24: if(Shift) printf("J"); else printf("j"); break;
            case 0x25: if(Shift) printf("K"); else printf("k"); break;
            case 0x26: if(Shift) printf("L"); else printf("l"); break;
            case 0x27: if(Shift) printf(":"); else printf(";"); break;
            case 0x28: if(Shift) printf("\""); else printf("'"); break;

            case 0x2C: if(Shift) printf("Z"); else printf("z"); break;
            case 0x2D: if(Shift) printf("X"); else printf("x"); break;
            case 0x2E: if(Shift) printf("C"); else printf("c"); break; // Odd. My notes said C pointed to 0x28...
            case 0x2F: if(Shift) printf("V"); else printf("v"); break;
            case 0x30: if(Shift) printf("B"); else printf("b"); break;
            case 0x31: if(Shift) printf("N"); else printf("n"); break;
            case 0x32: if(Shift) printf("M"); else printf("m"); break;
            case 0x33: if(Shift) printf("<"); else printf(","); break;
            case 0x34: if(Shift) printf(">"); else printf("."); break;
            case 0x35: if(Shift) printf("?"); else printf("/"); break;

            case 0x1C: printf("\n"); break; // Enter key
            case 0x39: printf(" "); break; // Space key
            case 0x2A: case 0x36: Shift = true; break;
            case 0xAA: case 0x86: Shift = false; break;

            case 0x3B: printf("\n                              ----- [About!] -----                              \n >> NanamiKeyboard keyboard driver version 1.04.25\n >> NanamiOS version 1.00.20 Codename \"Reimu\" [2023 Nov. 1]\n\n");
            //     ^- This should point to the F1 key. It does.
            case 0x3C: printf("                ----- NanamiOS 1.00.20[Codename \"Reimu\"] -----                \n --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid\n\nKernel: S-PHXKS - Build Date: 2023 November 1st\n\n[Caution!] Use this build at your risk. I haven't developed a lot of drivers or a command line yet, so it doesn't do much. Sorry! >_<\n[Caution!] In order to power NanamiOS off, you need to press the power button. You can't hit CTRL+ALT+DEL!!\n\nFor assistance, contact steelsofliquid@hotmail.com between 8 AM and 7 PM Eastern US & Canada Time.\n");
            //     ^- This should point to F2.
            // ughh, a 580-column line, with a missing semicolon... >_<

            case 0x3D: printf("                             ----- [TaskList] -----                             \n [Online] NanamiOS Kernel (S-PHXKS)     [Online] NanamiOS Interrupt Manager\n [Online] NanamiOS Global Desc.Table    [Online] NanamiOS Driver Manager\n [Online] NanamiKeyboard Driver         [Online] NanamiMouse Driver");
            //     ^- Should point to F3.

            case 0x3E: printf("                               ----- [Help] -----                               \n - F1: List version + Driver version.\n - F2: List technical information.\n - F3: List active tasks.\n - F4: Display help.");

            case 0x45: case 0xC5: break; // NumLock key. Some PCs don't have number pads.

            default:
            {
                char* foo = "Keyboard 0x00";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0x0F];
                foo[12] = hex[key & 0x0F];
                printf(foo);
                break;
            }
        }
    

    return esp;
}
