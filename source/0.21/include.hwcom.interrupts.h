
#ifndef __INTERRUPTS_H
#define __INTERRUPTS_H

#include "include.common.types.h"
#include "include.hwcom.port.h"
#include "include._.multitasking.h"
#include "include._.gdt.h"


    class InterruptManager;


    class InterruptHandler
    {
    protected:
        uint8_t interruptNumber;
        InterruptManager* interruptManager;

        InterruptHandler(InterruptManager* interruptManager, uint8_t interruptNumber);
        ~InterruptHandler();

    public:
        virtual uint32_t HandleInterrupt(uint32_t esp);

    };

    class InterruptManager
    {
    friend class InterruptHandler;

    protected:

        static InterruptManager* ActiveInterruptManager;
        InterruptHandler* handlers[256];
        TaskManager *taskManager;

        struct GateDescriptor
        {
            uint16_t handlerAddressLowBits;
            uint16_t gdt_codeSegmentSelector;
            uint8_t reserved;
            uint8_t access;
            uint16_t handlerAddressHighBits;

        } __attribute__((packed)); // 2024-10-31 ah yes, intellisense is totally fine and not drunk as this code compiled a-ok in the original ubuntu install
        // also why tf am i coding this on windows 10 garbage edition (poor timing for that joke -_-) when i could be doing this on linux

        static GateDescriptor interruptDescriptorTable[256];

        struct interruptDescriptorTablePointer
        {
            uint16_t size;
            uint32_t base;
        } __attribute__((packed));

        static void SetInterruptDescriptorTableEntry(
            uint8_t interruptNumber,
            uint16_t codeSegmentSelectorOffset,
            void (*handler)(),
            uint8_t DescriptorPrivilegeLevel,
            uint8_t DescriptorType
        );

        static void IgnoreInterruptRequest();

        static void HandleInterruptRequest0x00();
        static void HandleInterruptRequest0x01();
        static void HandleInterruptRequest0x02();
        static void HandleInterruptRequest0x03();
        static void HandleInterruptRequest0x04();
        static void HandleInterruptRequest0x05();
        static void HandleInterruptRequest0x06();
        static void HandleInterruptRequest0x07();
        static void HandleInterruptRequest0x08();
        static void HandleInterruptRequest0x09();
        static void HandleInterruptRequest0x0A();
        static void HandleInterruptRequest0x0B();
        static void HandleInterruptRequest0x0C();
        static void HandleInterruptRequest0x0D();
        static void HandleInterruptRequest0x0E();
        static void HandleInterruptRequest0x0F();
        static void HandleInterruptRequest0x31();


        static void HandleException0x00();
        static void HandleException0x01();
        static void HandleException0x02();
        static void HandleException0x03();
        static void HandleException0x04();
        static void HandleException0x05();
        static void HandleException0x06();
        static void HandleException0x07();
        static void HandleException0x08();
        static void HandleException0x09();
        static void HandleException0x0A();
        static void HandleException0x0B();
        static void HandleException0x0C();
        static void HandleException0x0D();
        static void HandleException0x0E();
        static void HandleException0x0F();
        static void HandleException0x10();
        static void HandleException0x11();
        static void HandleException0x12();
        static void HandleException0x13();


        static uint32_t handleInterrupt(uint8_t interruptNumber, uint32_t esp);
        uint32_t DoHandleInterrupt(uint8_t interruptNumber, uint32_t esp);

        Port8BitSlow picMasterCommand; // "Good morning, master! Is there anything I can do for you today?" - Touko. Me: "Cosplay Nanami Madobe AGAIN." Lol. Get it? 'cuz I'm such a "rebel" in the eyes of Microsoft and use Windows 10 instead of Windows 10 Autism (aka Windows 11)?
        Port8BitSlow picMasterData;
        Port8BitSlow picSlaveCommand; // You think this is slavery? Kyahahahaha! Iie! (No!) This is part of the Master/Slave System that usually gets called something else these days!
        Port8BitSlow picSlaveData;


    public:
        InterruptManager(uint16_t HardwareInterruptOffset, GlobalDescriptorTable* gdt, TaskManager* taskManager);
        ~InterruptManager();
        uint16_t HardwareInterruptOffset();

        void Activate();
        void Deactivate();

    };

#endif