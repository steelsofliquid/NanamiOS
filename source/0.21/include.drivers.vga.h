// This builds off of the mouse driver's base first xx lines as a framework.

#ifndef __VGA_H // Using the keyboard driver as a template
#define __VGA_H

    #include "include.common.types.h"
    #include "include.drivers.driver.h"
    #include "include.hwcom.port.h"
    // No need for interrupts.h here... I think.

    // Kyahahahaha!!!
    // Ah-lalalalalalalala!!

    // It's gonna be eleven-port madness!!

    class VideoGraphicsArray
    {
    protected:
    // Kyaaa!! So many ports!! >.^
    // How da hail do you portray >_< and ^.^ in the same ASCII emoticon?
        Port8Bit MiscPort; // MP
        Port8Bit CRTCIndexPort; // CTRCIP
        Port8Bit CRTCDataPort; // CTRCDP
        Port8Bit SequencerIndexPort; // SIP
        Port8Bit SequencerDataPort; // SDP
        Port8Bit GCIndexPort; // GCIP (Graphics Controller Index Port)
        Port8Bit GCDataPort; // GCDP (Graphics Controller Data Port)
        Port8Bit ACIndexPort; // ACIP (Attribute Controller Index Port)
        Port8Bit ACReadPort; // ACReaP (Attribute Controller Read Port)
        Port8Bit ACWritePort; // ACWP (Attribute Controller Write Port)
        Port8Bit ACResetPort; // ACResP (Attribute Controller Reset Port)

        void WriteRegisters(uint8_t* registers);
        uint8_t* GetFrameBufferSegment();

        virtual uint8_t GetColorIndex(uint8_t r, uint8_t g, uint8_t b);
    
    public:
        VideoGraphicsArray();
        ~VideoGraphicsArray();

        virtual bool SupportsMode(uint32_t width, uint32_t height, uint32_t colordepth);
        virtual bool SetMode(uint32_t width, uint32_t height, uint32_t colordepth);
        virtual void PutPixel(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b);
        virtual void PutPixel(uint32_t x, uint32_t y, uint8_t colorIndex);

        virtual void FillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t r, uint8_t g, uint8_t b);

    };


#endif