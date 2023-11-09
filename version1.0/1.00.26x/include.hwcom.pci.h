
// PCI is short for "Peripheral Component Interconnect".
// (I just shortened it to PCI here though the video uses the full
// name of this system (PCI is what I'm referring to) as I want my code
// to be rather simple)

// This file focuses on getting NanamiOS to work with PCI devices.

// To learn more about PCI, you can read up on any info about it
// on Wikipedia. Just like you can look up barebones info about Nanami Madobe
// there, too!

#ifndef __PCI_H
#define __PCI_H

#include "include.hwcom.port.h"
#include "include.common.types.h"
#include "include.hwcom.interrupts.h"
#include "include.drivers.driver.h"

    class PCIDevDesc // Short for "PCI Device Descriptor", or "PeripheralComponentInterconnectDeviceDescriptor".
    {
    public:
        uint32_t portBase;
        uint32_t interrupt; // I don't remember this being in the interrupts header...

        uint16_t bus;
        uint16_t device;
        uint16_t function;

        uint16_t vendor_id; // Up to 65 thousand vendor IDs can be assigned.
        uint16_t device_id;

        uint8_t class_id;
        uint8_t subclass_id;
        uint8_t interface_id;

        uint8_t revision;


        PCIDevDesc();
        ~PCIDevDesc();

    };

    class PCIController
    {
        Port32Bit dataPort;
        Port32Bit commandPort;

    public:
        PCIController();
        ~PCIController();

        uint32_t PCIRead(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset);
        void PCIWrite(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value);
        bool DeviceHasFunctions(uint16_t bus, uint16_t device);

        void SelectDrivers(DriverManager* driverManager);
        PCIDevDesc GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function);

    };

#endif