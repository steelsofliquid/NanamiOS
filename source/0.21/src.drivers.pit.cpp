// First non-WYOOS component. If it looks similar to osakaOS (which, I need to make a confession, I've been peeking at its source code often), well, I used the OSDev Wiki and that code is similar to that of osakaOS.

#include "include.drivers.pit.h"

        ProgrammableIntervalTimer::ProgrammableIntervalTimer() :

            Channel0(0x40),
            Channel1(0x41),
            Channel2(0x42),
            PITComPort(0x43)
        {
        }

		ProgrammableIntervalTimer::~ProgrammableIntervalTimer()
        {
        }

        uint32_t ProgrammableIntervalTimer::ReadPIT()
        {
            uint32_t count = 0;

            asm("cli");

            PITComPort.Write(0b0000000);
            count = Channel0.Read(); // Low
            count |= Channel0.Read() << 8; // High

            asm("sti");
            return count;
        }

        void ProgrammableIntervalTimer::SetPITCount(uint32_t count)
        {
            asm("cli");

            Channel0.Write(count);
            Channel0.Write(count >> 8);

            asm("sti");
        }