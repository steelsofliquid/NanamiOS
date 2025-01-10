// r_nanamitsukasa says on the 2nd of july 2024 at 01:05 toronto: crt means "cathode ray tube".

#include "include.drivers.vga.h"





VideoGraphicsArray::VideoGraphicsArray() :
    MiscPort(0x3C2),
    CRTCIndexPort(0x3D4),
    CRTCDataPort(0x3D5),
    SequencerIndexPort(0x3C4),
    SequencerDataPort(0x3C5),
    GCIndexPort(0x3CE),
    GCDataPort(0x3CF),
    ACIndexPort(0x3C0),
    ACReadPort(0x3C1),
    ACWritePort(0x3C0),
    ACResetPort(0x3DA)
{
}

VideoGraphicsArray::~VideoGraphicsArray()
{
}



void VideoGraphicsArray::WriteRegisters(uint8_t* registers)
{
    // for the miscellaneous port
    MiscPort.Write(*(registers++)); // r_nanamitsukasa at 00:56 est on 2024-07-02 ~ wow i'm tired and stuff... almost implemented this the wrong way
    
    // for the sequencer ports
    for(uint8_t i = 0; i < 5; i++)
    {
        SequencerIndexPort.Write(i);
        SequencerDataPort.Write(*(registers++));
    }

    // for the crt controller ports
    CRTCIndexPort.Write(0x03);
    CRTCDataPort.Write(CRTCDataPort.Read() | 0x80);
    CRTCIndexPort.Write(0x11);
    CRTCDataPort.Write(CRTCDataPort.Read() & ~0x80);

    registers[0x03] = registers[0x03] | 0x80;
    registers[0x11] = registers[0x11] & ~0x80;

    for(uint8_t i = 0; i < 25; i++)
    {
        CRTCIndexPort.Write(i);
        CRTCDataPort.Write(*(registers++));
    }

    // for the graphics controller ports
    for(uint8_t i = 0; i < 9; i++)
    {
        GCIndexPort.Write(i);
        GCDataPort.Write(*(registers++));
    }

    // for the attribute controller ports
    for(uint8_t i = 0; i < 21; i++)
    {
        ACResetPort.Read();

        ACIndexPort.Write(i);
        ACWritePort.Write(*(registers++));
    }

    ACResetPort.Read();
    ACIndexPort.Write(0x20);
}

bool VideoGraphicsArray::SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth)
{
    return width == 320 && height == 200 && colordepth == 8;
}

bool VideoGraphicsArray::SetMode(uint32_t width, uint32_t height, uint32_t colordepth)
{
    if(!SupportsMode(width, height, colordepth))
        return false;

    unsigned char g_320x200x256[] =
    {
        // misc
        0x63,

        // seq
        0x03, 0x01, 0x0F, 0x00, 0x0E,

        // crtc
        0x55, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
        0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x9C, 0x0E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
        0xFF,

        // gc
        0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
        0xFF,

        // ac
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x41, 0x00, 0x0F, 0x00, 0x00
    };

    WriteRegisters(g_320x200x256);
    return true;
}



uint8_t* VideoGraphicsArray::GetFrameBufferSegment()
{
    GCIndexPort.Write(0x06);
    uint8_t SegmentNumber = ((GCDataPort.Read() >> 2) & 0x03);

    switch(SegmentNumber)
    {
        default:

        case 0: return (uint8_t*)0x00000;
        case 1: return (uint8_t*)0xA0000;
        case 2: return (uint8_t*)0xB0000;
        case 3: return (uint8_t*)0xB8000;

    }
}

void VideoGraphicsArray::PutPixel(uint32_t x, uint32_t y, uint8_t colorIndex)
{
    uint8_t* PixelAddress = GetFrameBufferSegment() + 320*y + x;
    *PixelAddress = colorIndex;
}

uint8_t VideoGraphicsArray::GetColorIndex(uint8_t r, uint8_t g, uint8_t b)
{
    if(r == 0x00, g == 0x00, b == 0xA8)
        return 0x01;
}

void VideoGraphicsArray::PutPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    PutPixel(x, y, GetColorIndex(r,g,b));
}

void VideoGraphicsArray::FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b)
{
  for(int32_t Y = y; Y < y+h; Y++)
    for(int32_t X = x; X < x+w; X++)
      PutPixel(X, Y, r, g, b);

}
