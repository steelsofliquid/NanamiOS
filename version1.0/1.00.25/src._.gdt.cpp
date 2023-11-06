
#include "include._.gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable() // GDT, not GPT or ChatGPT. Is there even a thing as "ChatGDT"? Meh, probably. Probably some goofy ahh bootleg ChatGPT.
: nullSegmentSelector(0,0,0),
unusedSegmentSelector(0,0,0),
codeSegmentSelector(0,64*1024*1024, 0x9A),
dataSegmentSelector(0,64*1024*1024, 0x92)
{
    uint32_t i[2];
    i[1] = (uint32_t)this;  // DO NOT SWAP THESE TWO VALUES. IT WILL BREAK THE OS!!
    i[0] = sizeof(GlobalDescriptorTable) << 16;

// Swapped the 0 and 1, got a glitch, and swapped them back. Let's see how that works!

    asm volatile("lgdt (%0)": :"p" (((uint8_t *) i)+2));
}

GlobalDescriptorTable::~GlobalDescriptorTable() // just realized here there's supposed to be a () i'm such a baka
{
    // nothing to report here... for now.
}

uint16_t GlobalDescriptorTable::DataSegmentSelector()
{
    return (uint8_t*)&dataSegmentSelector - (uint8_t*)this;
}

uint16_t GlobalDescriptorTable::CodeSegmentSelector()
{
    return (uint8_t*)&codeSegmentSelector - (uint8_t*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags)
{
    uint8_t* target = (uint8_t*)this;

    if(limit <= 65536)
    {
        target[6] = 0x40;
    }
    else
    {
        if((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12)-1;
        else
            limit = limit >>12;
        
        target[6] = 0xC0;
    }

    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    target[5] = flags;

}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base()
{
    // well, there is stuf that goes here! the video didn't show it at first!
    
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[7]; // Pretty sure this isn't supposed to be a Nanami Madobe/Windows 7 reference. Because it's not.
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];
    return result;

}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    uint8_t* target = (uint8_t*)this;
    uint32_t result = target[6] & 0xF; // "MUTSUMI MADOBE IN NANAMI MADOBE OS!?!?!?!?!?!!?!?!?!?111/??" O_O lol, couldn't help it ^_^
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;

}