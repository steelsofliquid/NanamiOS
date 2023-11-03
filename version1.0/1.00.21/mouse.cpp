
#include "mouse.h"

MouseDriver::MouseDriver(InterruptManager* manager)
: InterruptHandler(0x2C, manager),
dataport(0x60),
commandport(0x64)
{
    //
}

MouseDriver::~MouseDriver()
{
    //
}

void MouseDriver::Activate()
{
    offset = 0;
    buttons = 0;

    uint16_t* VideoMemory = (uint16_t*)0xb8000;
    VideoMemory[80*12+40] = ((VideoMemory[80*12+40] & 0xF000) >> 4)
                    | ((VideoMemory[80*12+40] & 0xF000) << 4)
                    | ((VideoMemory[80*12+40] & 0x00FF));

    commandport.Write(0xA8); // Activate interrupts
    commandport.Write(0x20); // Get current state
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60); // Set the state
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();
}

// void printf(char*);
// ^^-- Is this the problem? It might be...

uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();
    if(!(status & 0x20))
        return esp;


    static int8_t x=40,y=12;

    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;

    if(offset == 0)
    {
        if(buffer[1] != 0 || buffer[2] != 0)
        {
            static uint16_t* VideoMemory = (uint16_t*)0xb8000; // The video memory is the same for all GPUs for now. It doesn't matter if your PC has a flashy brand-new RTX or an ancient Voodoo. NanamiOS treats both cards equally.

            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xF000) >> 4
                                | (VideoMemory[80*y+x] & 0xF000) << 4
                                | (VideoMemory[80*y+x] & 0x00FF);

            x += buffer[1];
            if(x < 0) x = 0;
            if(x >= 80) x = 79;

            y -= buffer[2];
            if(y < 0) y = 0;
            if(y >= 25) y = 24;

            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xF000) >> 4
                                | (VideoMemory[80*y+x] & 0xF000) << 4
                                | (VideoMemory[80*y+x] & 0x00FF);
    
        }
    /*
        for(uint8_t i = 0; i < 4; i++)
        {
            if((buffer[0] & (0x01 << i)) != (buttons & (0x01<<i)))
            {
                VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                                    | ((VideoMemory[80*y+x] & 0xF000) << 4)
                                    | ((VideoMemory[80*y+x] & 0x00FF));
            }
        }
        buttons = buffer[0];
        */
    }

    return esp;
}
