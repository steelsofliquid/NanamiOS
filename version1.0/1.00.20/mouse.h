
#ifndef __MOUSE_H // Using the keyboard driver as a template
#define __MOUSE_H

    #include "types.h"
    #include "interrupts.h"
    #include "driver.h"
    #include "port.h"

    class MouseDriver : public InterruptHandler, public Driver
    {
        Port8Bit dataport;
        Port8Bit commandport; // from keyboard driver

        uint8_t buffer[3];
        uint8_t offset;
        uint8_t buttons;

        int8_t x, y;
    public:
        MouseDriver(InterruptManager* manager);
        ~MouseDriver();
        virtual uint32_t HandleInterrupt(uint32_t esp);
        virtual void Activate();

    };


#endif