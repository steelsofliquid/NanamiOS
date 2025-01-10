/* I had to use code from another OS. I didn't want to resort to using source from another OS,
but I could not find ANYWHERE on the internet on how to implement a command line. In the future,
I may find a way to rewrite the code in another way. >_< 

I typically feel too embarrassed to explain why I use code from other sources. And because I feel
extremely embarassed using other's source code and such, it's purely the code needed to get the
command line to work, as I wanted to add a command line but didn't know how to implement one.*/

// Also, don't compile the code yet. It uses code for features not yet added.

#ifndef __NANAMICL_H
#define __NANAMICL_H

    #include "include.common.types.h"
    #include "include._.multitasking.h" // Currently does not exist
    #include "include._.gdt.h"

    class NanamiCL
    {
        public:
            void (*ComTbl[65536])(char*, NanamiCL*);
            uint32_t VarTable[1024];
            bool CondIf;
            bool CondLoop;
            uint32_t ReturnValue = 0;

            uint16_t ComList[65536];
            uint16_t ComIndex = 0;

            GlobalDescriptorTable* nanamicl_x_nanamigdt;
            TaskManager* nanamicl_x_nostm; // nostm refers to NanamiOS Task Manager here. I try to use unique naming and such.
            // Also, currently, as of build 29, Task Manager does not exist.

        public:
            char* ComString;
            char* command(char* cmd, uint8_t length);

            void hash_add(char *cmd, void func(char*, NanamiCL*));
            void hash_cli_init();

            void getTM(GlobalDescriptorTable* gdt, TaskManager* tm);
    
    }

#endif