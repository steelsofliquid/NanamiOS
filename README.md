# NanamiOS
An actual operating system made by me. Naming influenced by my favorite anime character of all time (Nanami Madobe).

# _What is NanamiOS?_
Unlike Steel OS (an operating environment), NanamiOS is an actual operating system that you can load onto a CD, and boot the OS off of that CD (trust me, I've tested it myself). It is written in C++ and Assembly, and the code is based off of tutorial code from Write your own Operating System videos.
NanamiOS is currently in a very primitive stage, and for this reason, don't daily drive it. It can't do anything, as it doesn't have a graphics mode, command line, or even drivers. But, from hardware testing and if my theory is correct, you can possibly run this on hardware as old as the original Intel
i386 processor, 32 megabytes of RAM _(I've tested it and it works under 64 megabytes)_, and other legacy hardware.

# _System Requirements_
To run NanamiOS, you should probably use VirtualBox 7.0 to run it. Use this configuration:
* 64 megabytes of RAM
* 1 Core processor
* Default video memory
* 2 gigabyte hard disk
* CD drive



If you want to run NanamiOS on physical hardware, it's possible, but I don't recommend it at the moment. I've tested it myself using a 2006 Toshiba Tecra A8-EZ8313 and it works; you don't even need to format your disk to run the OS. Please take the requirements with a grain of salt. You will need the following:
* Intel i386 processor
* 32 megabytes of RAM
* 2 gigabyte disk
* CD-ROM drive
* Keyboard (to get into the boot menu)
* A monitor

# _Questions & Answers_
__How did you come up with the name "NanamiOS"?__



* _I was split between calling the OS "NanamiOS" and "KitsuneOS", and decided on "NanamiOS". I named the OS after Nanami Madobe, an OS-tan character used to personify Windows 7, because she is my favorite fictional character ever, and if you want a bit of a history lesson, Python's creator named the language after Monty Python, a comedy group which the creator of Python enjoyed watching, so people name their projects after things they enjoy if you're curious!_



__I tried rebooting using Control, Alt, and Delete. Nothing happened! What do I do?__



* _That won't do anything, as a keyboard driver isn't present. You need to press the power button (no need to hold it)._