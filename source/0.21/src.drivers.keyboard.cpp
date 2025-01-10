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

            case 0x3B: 
            {
                printf("\n");
                printf(" KB MS                                Help               ----/--/-- --:--       ");
                printf("                                                                                ");
                printf(" Welcome to Nanami/OS!                                                          ");
                printf(" There is currently no shell, so how you are seeing this is through hardcoded   ");
                printf(" implementations in the keyboard driver. For support/assistance, please contact ");
                printf(" this e-mail, shown on the left. Keys include:   /--------------------------\\   ");
                printf(" [F1] Help   [F2] About                          |steelsofliquid@hotmail.com|   ");
                printf("                                                 \\__________________________/   ");
                break;
                }
            //     ^- This should point to the F1 key. It does.
            case 0x3C:
            {
                printf("\n");
                printf(" KB MS                               About               ----/--/-- --:--       ");
                printf("                                                                                ");
                printf(" Nanami/OS (Version 0.21 Build 34 \"Reimu\")      This software uses code from:   "); // For exact 0.21.33 code just remove the two spaces at the end
                printf("Nanami/OS Copyright (C) 2024 SteelsOfLiquid.       - WYOOS Tutorial (mostly)    ");
                printf("This software comes with ABSOLUTELY ZERO WARRANTY. - osakaOS (pit driver and    ");
                printf("This is free software, and you are welcome to                 pc speaker)       ");
                printf("resdistribute it under certain conditions.                                      ");
                printf("                                                                                ");
                printf(" *** LICENSE NOT INCLUDED DUE TO LACK OF FILESYSTEM                             ");
                break;
            }
            //     ^- This should point to F2.
            // ughh, a 580-column line, with a missing semicolon... >_<

            case 0x3D: break;
            //     ^- Should point to F3.

            case 0x3E: break;

            case 0x3F: // F5 iirc
            {
                break;
            }


            case 0x40:
            {
                break;
            }


            case 0x41:  // This should point to F7...
            {
                printf("command►");
                break;
            
            }

            case 0x42: printf("¬"); break; // F8, notsign key
            case 0x43: printf("♫"); break; // F9, beamed notes key
            case 0x44: printf("♥"); break; // F10, heart key

            case 0x45: case 0xC5: break; // NumLock key. Some PCs don't have number pads.

            default:
            {
                //printf("KB:0x");
                //printfHex(key);
                //break;
            }
        }
    

    return esp;
}
