// My first driver! ^_^

#include "keyboard.h"

KeyboardDriver::KeyboardDriver(InterruptManager* manager)
: InterruptHandler(0x21, manager),
dataport(0x60),
commandport(0x64)
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

KeyboardDriver::~KeyboardDriver()
{
    //
}

void printf(char*);

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    if(key < 0x80)
    {

        switch(key)
        {
            case 0xFA: break;
            case 0x1E: printf("a"); break; // Original code stated "this key (a) is assigned to hex 0x1E". I watched the video, and it turns out, that's the A key! So, that's a start!
            // This is only how far this goes. I still need to get the rest of the keys mapped, so all of you testers can rejoice!
            // That is, if the build works, and you know my e-mail and have a piece of paper!
            case 0x45: case 0xC5: break;

            default:
            {
                char* foo = "\n[NanamiKeyboard] 0x00 - Keystroke from that key has been obtained!";
                char* hex = "0123456789ABCDEF";
                foo[11] = hex[(key >> 4) & 0x0F];
                foo[12] = hex[key & 0x0F];
                printf(foo);
                break;
            }
        }
    }

    return esp;
}
