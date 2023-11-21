// My first driver! ^_^

#include "include.drivers.keyboard.h"


KeyboardEventHandler::KeyboardEventHandler()
{
    //
}
        
void KeyboardEventHandler::OnKeyDown(char)
{
    //
}

void KeyboardEventHandler::OnKeyUp(char)
{
    //
}


KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
: InterruptHandler(manager, 0x21),
dataport(0x60),
commandport(0x64)
{
    this->handler = handler;
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
void printfHex(uint8_t);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    if(handler == 0)
        return esp;

    static bool Shift = false;

        switch(key)
        {
            case 0xFA: break;

            case 0x29: if(Shift) handler->OnKeyDown('~'); else handler->OnKeyDown('`'); break;
            case 0x02: if(Shift) handler->OnKeyDown('!'); else handler->OnKeyDown('1'); break;
            case 0x03: if(Shift) handler->OnKeyDown('@'); else handler->OnKeyDown('2'); break;
            case 0x04: if(Shift) handler->OnKeyDown('#'); else handler->OnKeyDown('3'); break;
            case 0x05: if(Shift) handler->OnKeyDown('$'); else handler->OnKeyDown('4'); break;
            case 0x06: if(Shift) handler->OnKeyDown('%'); else handler->OnKeyDown('5'); break;
            case 0x07: if(Shift) handler->OnKeyDown('^'); else handler->OnKeyDown('6'); break;
            case 0x08: if(Shift) handler->OnKeyDown('&'); else handler->OnKeyDown('7'); break;
            case 0x09: if(Shift) handler->OnKeyDown('*'); else handler->OnKeyDown('8'); break;
            case 0x0A: if(Shift) handler->OnKeyDown('('); else handler->OnKeyDown('9'); break;
            case 0x0B: if(Shift) handler->OnKeyDown(')'); else handler->OnKeyDown('0'); break;
            case 0x0C: if(Shift) handler->OnKeyDown('_'); else handler->OnKeyDown('-'); break;
            case 0x0D: if(Shift) handler->OnKeyDown('+'); else handler->OnKeyDown('='); break;

            case 0x0F: printf("     "); break; // Tab key. Also, the only surviving "printf" system as my compiler gave me a warning that it may cause an overflow.
            case 0x10: if(Shift) handler->OnKeyDown('Q'); else handler->OnKeyDown('q'); break;
            case 0x11: if(Shift) handler->OnKeyDown('W'); else handler->OnKeyDown('w'); break;
            case 0x12: if(Shift) handler->OnKeyDown('E'); else handler->OnKeyDown('e'); break;
            case 0x13: if(Shift) handler->OnKeyDown('R'); else handler->OnKeyDown('r'); break;
            case 0x14: if(Shift) handler->OnKeyDown('T'); else handler->OnKeyDown('t'); break;
            case 0x15: if(Shift) handler->OnKeyDown('Y'); else handler->OnKeyDown('y'); break;
            case 0x16: if(Shift) handler->OnKeyDown('U'); else handler->OnKeyDown('u'); break;
            case 0x17: if(Shift) handler->OnKeyDown('I'); else handler->OnKeyDown('i'); break;
            case 0x18: if(Shift) handler->OnKeyDown('O'); else handler->OnKeyDown('o'); break;
            case 0x19: if(Shift) handler->OnKeyDown('P'); else handler->OnKeyDown('p'); break;
            case 0x1A: if(Shift) handler->OnKeyDown('{'); else handler->OnKeyDown('['); break;
            case 0x1B: if(Shift) handler->OnKeyDown('}'); else handler->OnKeyDown(']'); break;
            case 0x2B: if(Shift) handler->OnKeyDown('|'); else handler->OnKeyDown('\\'); break; // A second backslash is deployed, because purely one backslah will just break the code.

            case 0x1E: if(Shift) handler->OnKeyDown('A'); else handler->OnKeyDown('a'); break; // Original code stated "this key (a) is assigned to hex 0x1E". I watched the video, and it turns out, that's the A key! So, that's a start!
            case 0x1F: if(Shift) handler->OnKeyDown('S'); else handler->OnKeyDown('s'); break;
            case 0x20: if(Shift) handler->OnKeyDown('D'); else handler->OnKeyDown('d'); break;
            case 0x21: if(Shift) handler->OnKeyDown('F'); else handler->OnKeyDown('f'); break;
            case 0x22: if(Shift) handler->OnKeyDown('G'); else handler->OnKeyDown('g'); break;
            case 0x23: if(Shift) handler->OnKeyDown('H'); else handler->OnKeyDown('h'); break;
            // case 0x17: printf("I"); break; NOT SUPPOSED TO BE IN THIS ROW!!! >_<
            case 0x24: if(Shift) handler->OnKeyDown('J'); else handler->OnKeyDown('j'); break;
            case 0x25: if(Shift) handler->OnKeyDown('K'); else handler->OnKeyDown('k'); break;
            case 0x26: if(Shift) handler->OnKeyDown('L'); else handler->OnKeyDown('l'); break;
            case 0x27: if(Shift) handler->OnKeyDown(':'); else handler->OnKeyDown(';'); break;
            case 0x28: if(Shift) handler->OnKeyDown('\"'); else handler->OnKeyDown('\''); break;

            case 0x2C: if(Shift) handler->OnKeyDown('Z'); else handler->OnKeyDown('z'); break;
            case 0x2D: if(Shift) handler->OnKeyDown('X'); else handler->OnKeyDown('x'); break;
            case 0x2E: if(Shift) handler->OnKeyDown('C'); else handler->OnKeyDown('c'); break; // Odd. My notes said C pointed to 0x28...
            case 0x2F: if(Shift) handler->OnKeyDown('V'); else handler->OnKeyDown('v'); break;
            case 0x30: if(Shift) handler->OnKeyDown('B'); else handler->OnKeyDown('b'); break;
            case 0x31: if(Shift) handler->OnKeyDown('N'); else handler->OnKeyDown('n'); break;
            case 0x32: if(Shift) handler->OnKeyDown('M'); else handler->OnKeyDown('m'); break;
            case 0x33: if(Shift) handler->OnKeyDown('<'); else handler->OnKeyDown(','); break;
            case 0x34: if(Shift) handler->OnKeyDown('>'); else handler->OnKeyDown('.'); break;
            case 0x35: if(Shift) handler->OnKeyDown('?'); else handler->OnKeyDown('/'); break;

            case 0x1C: handler->OnKeyDown('\n'); break; // Enter key
            case 0x39: handler->OnKeyDown(' '); break; // Space key
            case 0x2A: case 0x36: Shift = true; break;
            case 0xAA: case 0x86: Shift = false; break;

            case 0x3B: printf("\n------------------------------------[About!]------------------------------------\n >> NanamiKeyboard keyboard driver version 1.08.47\n >> NanamiOS version 1.00.28 Codename \"Reimu\" [2023 Nov. 20]\n\n"); break;
            //     ^- This should point to the F1 key. It does.
            case 0x3C: printf("                 ----- NanamiOS 1.00.28[Codename \"Reimu\"] -----                 \n --- By SteelsOfLiquid - https://www.youtube.com/@steelsofliquid\n\nKernel: S-PHXKS - Build Date: 2023 November 20th\n\n[Caution!] Use this build at your risk. I haven't developed a lot of drivers or a command line yet, so it doesn't do much. Sorry! >_<\n[Caution!] In order to power NanamiOS off, you need to press the power button. You can't hit CTRL+ALT+DEL!!\n\nFor assistance, contact steelsofliquid@hotmail.com between 8 AM and 7 PM Eastern US & Canada Time.\n"); break;
            //     ^- This should point to F2.
            // ughh, a 580-column line, with a missing semicolon... >_<

            case 0x3D: printf("-----------------------------------[TaskList]-----------------------------------\n [Online] NanamiOS Kernel (S-PHXKS)     [Online] NanamiOS Interrupt Manager\n [Online] NanamiOS Global Desc.Table    [Online] NanamiOS Driver Manager\n [Online] NanamiKeyboard Driver         [Online] NanamiMouse Driver\n [Online] NanamiPCI                     \n"); break;
            //     ^- Should point to F3.

            case 0x3E: printf("-------------------------------------[Help]-------------------------------------\n   -- Commands --\n - F1: NanamiOS Version Reporter\n - F2: NanamiOS RetroCosplay.\n - F3: NanamiOS Task Manager\n - F4: NanamiOS Help Viewer\n - F5: NanamiOS Team Reporter\n - F6: NanamiOS System Information\n - F7: Turn on graphics mode.\n\nFOR DEVELOPERS: Please read the NanamiOS 1.00 SuperGuide!\n"); break;

            case 0x3F: // F5 iirc
            {
                printf("-----------------------------------[Credits!]-----------------------------------");
                printf("-- NanamiOS 1.00 Codename \"Reimu\", developed 2023-202x(?)");
                printf("\nDEVELOPERS:");
                printf("\n - Steel Renaud (SteelsOfLiquid)   - Nathan Renaud (supernathanrenaud5000)");
                printf("\nORIGINAL TUTORIAL:");
                printf("\nOriginal tutorial by Write your own Operating System");
                printf("\nSOFTWARE:");
                printf("\n - MS Visual Studio Code   - Ubuntu 23.04   - G++ compiler");
                printf("\n - GNU MTools   - Oracle VM VirtualBox 7.0   - ImgBurn 2.5.8");
                printf("\nSPECIAL THANKS:");
                printf("\n - Paige (my sister)   - All NanamiOS alpha/beta testers");
                printf("\n - Nanami Madobe (the inspiration of this project)   - ZUN (developer of Touhou)");
                printf(" - The GNU project\n");
                printf("\n   Nanami Madobe was created by artist Wakaba for Techno-Alliance Corp, also    ");
                printf(" known as Windows 7 Mania, to promote Microsoft Windows 7. This OS is dedicated ");
                printf("to Nanami-chan, but she is NOT associated with NanamiOS, outside of a variant I ");
                printf("                                     made.                                      ");
                break;
            }


            case 0x40:
            {
                printf("-------------------------[NanamiOS System Information!]-------------------------");
                printf("                                                                                ");
                printf("  --- ---      System  : NanamiOS         Version : 1.00.28x                    ");
                printf(" -   -   -     DevStage: Alpha            BuldDate: 2023-11-20                  ");
                printf("  -     -      Drivers : 3                Publishr: SteelsOfLiquid              ");
                printf("   -   -       Kernel  : S-PHXKS          BootMngr: GRUB                        ");
                printf(" |  - -  |                                                                      ");
                printf(" |   -   |                                                                      ");
                printf("  _______/                                                                      ");
                printf("                                                                                ");
                printf("                                                                                ");
                break;
            }


            case 0x41:  // This should point to F7...
            {
                printf("[Note, 1/2] NanamiVGA is a system driver that is injected into the kernel.\n");
                printf("[Note, 2/2] NanamiVGA is also included with NanamiOS, as it is a core component.");
                printf("[Error] Error occured while trying to load VGA mode!\n");
                printf("\n");
                printf("     It appears you're trying to access the graphics mode. However, this mode is");
                printf("not yet available. Though NanamiOS is intended for GUI use, this mode has yet to");
                printf("be developed. Plus, VGA drivers haven't been developed yet.");
                printf("\n");
                printf("\n");
                break;
            
            }

            case 0x45: case 0xC5: break; // NumLock key. Some PCs don't have number pads.

            default:
            {
                //printf("Keyboard 0x");
                //printfHex(key);
                //break;
            }
        }
    

    return esp;
}
