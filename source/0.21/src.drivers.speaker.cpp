#include "include.drivers.speaker.h"

void sleep(uint32_t interval);

Speaker::Speaker()
 : PITChannel2(0x42),
   PITCom(0x43),
   SpeakerPort(0x61)
{
}

Speaker::~Speaker()
{
}

void Speaker::play_sound(uint32_t nFrequence)
{
    uint32_t Div;
	uint8_t tmp;

	Div = 1193180 / nFrequence;

	PITCom.Write(0xB6);
	PITChannel2.Write((uint8_t) (Div));
	PITChannel2.Write((uint8_t) (Div >> 8));
	
	tmp = SpeakerPort.Read();

	if (tmp != (tmp | 3)) {
		SpeakerPort.Write(tmp | 3);
	}
	
}

void Speaker::nosound()
{
    uint8_t tmp = SpeakerPort.Read();
	
	SpeakerPort.Write(tmp & 0xFC);
}

void Speaker::beep()
{
    play_sound(1000);
	sleep(10);
	nosound();
}