
#include "port.h"

Port::Port(uint16_t portnumber)
{
    this->portnumber = portnumber;
}

Port::~Port()
{
    // just some placeholder
}

Port8Bit::Port8Bit(uint16_t portnumber)
: Port(portnumber)
{
    // placeholder
}

Port8Bit::~Port8Bit()
{
    // nothing here either
}
void Port8Bit::Write(uint8_t data)
{
    // nanami
    // To anyone wondering why there's just a random comment saying "nanami", this part was built in a way where code wasn't implemented first.
    // So, I labelled these regions "placeholder", "nothing to see here", and then made the last two "nanami" and "madobe".
    // Kinda gives me vibes to one of my shoddy 2019 Audacity remixes called "Microsoft and Windows". Heh.
    
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (portnumber));
}
uint8_t Port8Bit::Read()
{
    // madobe
    // I already made ONE comment explaining why there's this random comment.
    // I'm not explaining it again. T_T

    uint8_t result;
    __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}


// 8-bit slow entry


Port8BitSlow::Port8BitSlow(uint16_t portnumber)
: Port8Bit(portnumber)
{
    // placeholder
}

Port8BitSlow::~Port8BitSlow()
{
    // nothing here either
}
void Port8BitSlow::Write(uint8_t data)
{
    // nanami madobe
    // the read system doesn't exist in the slow thingy
    
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a" (data), "Nd" (portnumber));
}



// 16-bit entry


Port16Bit::Port16Bit(uint16_t portnumber)
: Port(portnumber)
{
    // placeholder
}

Port16Bit::~Port16Bit()
{
    // nothing here either
}
void Port16Bit::Write(uint16_t data)
{
    // nanami
    // To anyone wondering why there's just a random comment saying "nanami", this part was built in a way where code wasn't implemented first.
    // So, I labelled these regions "placeholder", "nothing to see here", and then made the last two "nanami" and "madobe".
    // Kinda gives me vibes to one of my shoddy 2019 Audacity remixes called "Microsoft and Windows". Heh.
    
    __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (portnumber));
}
uint16_t Port16Bit::Read()
{
    // madobe
    // I already made ONE comment explaining why there's this random comment.
    // I'm not explaining it again. T_T

    uint16_t result;
    __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}


// 32-bit entry


Port32Bit::Port32Bit(uint16_t portnumber)
: Port(portnumber)
{
    // placeholder
}

Port32Bit::~Port32Bit()
{
    // nothing here either
}
void Port32Bit::Write(uint32_t data)
{
    // nanami
    // To anyone wondering why there's just a random comment saying "nanami", this part was built in a way where code wasn't implemented first.
    // So, I labelled these regions "placeholder", "nothing to see here", and then made the last two "nanami" and "madobe".
    // Kinda gives me vibes to one of my shoddy 2019 Audacity remixes called "Microsoft and Windows". Heh.
    
    __asm__ volatile("outl %0, %1" : : "a" (data), "Nd" (portnumber));
}
uint32_t Port32Bit::Read()
{
    // madobe
    // I already made ONE comment explaining why there's this random comment.
    // I'm not explaining it again. T_T

    uint32_t result;
    __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (portnumber));
    return result;
}

