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



__I'm getting this weird black screen with a bunch of gray and white text and pink lines. What do I do?__



* _Immediately. Press. The. Power. Button. I don't know what happens if you keep the screen going for longer periods of time. You probably experienced an interrupt, and one that the system doesn't know how to handle._



__What will happen to Steel OS?__



* _I'll likely keep it around, but use the interface in its current form as that of NanamiOS, and make drastic changes to Steel OS interface. In fact, I've already started to make said changes in Steel OS 4 Build 3011..._



__How can I trust this OS?__



* _Starting with NanamiOS 1.00 Build 10, (most) builds of NanamiOS are tested to make sure they don't experience crashes and issues. These tests can be comparison tests, endurance tests, feature tests, etc. - Besides, I wouldn't mainline a project I'd need my one of my old PCs to test that I'd know would cause damage to that computer!_
* _Besides, I also test this OS on physical hardware._
  * _Both desktops and laptops!_
