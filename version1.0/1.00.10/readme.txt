NanamiOS Version 1.0 [Codename: "Reimu"] Build 10

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
- Interrupts cause a triple fault. For that reason, they've been disabled.

Patch Notes:
- Reverted Build 10's GDT back from Build 9 to that of Build 8.
- Disabled interrupts.

What's new or changed:
Nothing.

Testing:
- Untimed endurance test, passed the test.

Readme Corrections:
- Fixed a typo in the patch notes saying it reverted 9's GDT to 10.
