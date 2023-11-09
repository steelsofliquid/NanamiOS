
// You can call it either "NanamiPCI" or "NanamiOS PCI Systems" for now. ^_^
// I'm fine with either; probably the former will be the final name. NanamiOS
// uses system components and stock/in-box programs using a mix of both
// SteelsOfLiquid Steel OS and Microsoft Windows naming conventions.

#include "include.hwcom.pci.h"


PCIDevDesc::PCIDevDesc()
{
}

PCIDevDesc::~PCIDevDesc()
{
}

PCIController::PCIController()
: dataPort(0xCFC),
  commandPort(0xCF8)
{
}

PCIController::~PCIController()
{
}

uint32_t PCIController::PCIRead(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset)
{
    uint32_t id =
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);
    commandPort.Write(id);
    uint32_t result = dataPort.Read();
    return result >> (8* (registeroffset % 4));

}

/* Build 26 on 2023 November 6th:
I named these two things "PCIRead" and "PCIWrite" because I didn't want to run into problems
with the normal "Read" and "Write" code. The original code stated "PerhipheralComponentInterconnectController", "Read", and "Write". */

void PCIController::PCIWrite(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value)
{
    uint32_t id =
        0x1 << 31
        | ((bus & 0xFF) << 16)
        | ((device & 0x1F) << 11)
        | ((function & 0x07) << 8)
        | (registeroffset & 0xFC);
    commandPort.Write(id);
    dataPort.Write(value);
    
}

bool PCIController::DeviceHasFunctions(uint16_t bus, uint16_t device)
{
    return PCIRead(bus, device, 0, 0x0E) & (1<<7);
}

void printf(char* str);
void printfHex(uint8_t);

void PCIController::SelectDrivers(DriverManager* driverManager)
{
    for(int bus = 0; bus < 8; bus++)
    {
        for(int device = 0; device < 32; device++)
        {
            int numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
            for(int function = 0; function < numFunctions; function++) // wow, that's 3 for loops, a for loop inside a for loop inside a for loop!
            {
                PCIDevDesc dev = GetDeviceDescriptor(bus, device, function);

                if(dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF) // got an error. perhaps, it's the = instead of ==?
                    break; // Kyaaaaa, these indents... >_<
                
                /*
                printf("[PCI] bus "); // almost forgot a semi-colon...
                printfHex(bus & 0xFF);

                printf(", device ");
                printfHex(device & 0xFF);

                printf(", function ");
                printfHex(function & 0xFF);

                printf(" -- vendor ");
                printfHex((dev.vendor_id & 0xFF00) >> 8);
                printfHex(dev.vendor_id & 0xFF);
                printf(" device ");
                printfHex((dev.device_id & 0xFF00) >> 8);
                printfHex(dev.device_id & 0xFF);

                printf("\n");
                */
               // Feel free to remove the comment pins to get more debug info. I did, for now.

            }
        }
    }
}

PCIDevDesc PCIController::GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function)
{
    PCIDevDesc result;

    result.bus = bus;
    result.device = device;
    result.function = function;

    result.vendor_id = PCIRead(bus, device, function, 0x00);
    result.device_id = PCIRead(bus, device, function, 0x02);

    result.class_id = PCIRead(bus, device, function, 0x0B);
    result.subclass_id = PCIRead(bus, device, function, 0x0A);
    result.interface_id = PCIRead(bus, device, function, 0x09);

    result.revision = PCIRead(bus, device, function, 0x08);
    result.interrupt = PCIRead(bus, device, function, 0x3C);

    return result;
}

