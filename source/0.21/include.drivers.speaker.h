#ifndef __SPEAKER_H
#define __SPEAKER_H

#include "include.common.types.h"
#include "include.drivers.driver.h"
#include "include.hwcom.port.h"

class Speaker
{
    public:
        Port8Bit PITChannel2;
        Port8Bit PITCom;
        Port8Bit SpeakerPort;

    public:
        Speaker();
        ~Speaker();

        void play_sound(uint32_t nFrequence);
        void nosound();
        void beep();

};

#endif