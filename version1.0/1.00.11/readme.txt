NanamiOS Version 1.0 [Codename: "Reimu"] Builds 11A & 11B

Note! Due to my lack of attention, I accidentally placed a portion of the code from Build 12's "interrupt.cpp" file in Build 11.

System Requirements:
- CD drive
- Intel i386 or better (Pentium 4 recommended)
- 64 megabytes of RAM
- 4 GB hard drive
- A display

Warnings:
- Drivers are not provided in this version. It is very primitive and doesn't yet have driver support.
- If you want to run this on physical hardware, do so at your own risk. Nothing should go wrong, but I recommend you boot off of a CD.

Known Issues:
- Command Line doesn't exist.
- Drivers don't exist.

Patch Notes:
- Fixed an issue where interrupts cause triple faults or video memory glitches.
- [11B only] Fixed an issue where the build date said 2023 October 28th, it is now correct.
- [11B only] Added back the interrupt system to go off.

What's new or changed:
- [11A] Nothing.
- [11B] Added a system message saying that it is an experimental build.

Testing
- [11A] This build has not undergone any testing, but should behave just like NanamiOS 1.00 Build 10.
- [11B] a 30-minute endurance test, passed with a final uptime number of 36 minutes, 40 seconds, with the session being closed without issues via being shut down by me.
