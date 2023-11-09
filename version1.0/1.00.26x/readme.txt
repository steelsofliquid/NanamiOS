NanamiOS Version 1.00 [Codename: "Reimu"] Builds 26A, 26B, 26C, and 26D

System Requirements:
- CD drive
- Intel i386 or better (Pentium 4 recommended)
- 64 megabytes of RAM
- 4 GB hard drive
- A display

Warnings:
- Only two drivers are provided in this version. It is very primitive and has almost no driver support, apart from a keyboard driver and a mouse driver.
- If you want to run this on physical hardware, do so at your own risk. Boot off of a CD.

Known Issues:
- Command Line doesn't exist.
- Only two drivers exist.
- No backspace key.
- USB support on physical hardware sucks a$$.
- PS/2 support is perhaps even worse.
- 26A and 26B try to boot to "shpxkskernel.bin", when the bin it's supposed to boot to is "sphxkskernel.bin". This causes an issue with GRUB.

Patch Notes:
- 26C and 26D fix the issues in 26B and 26A mentioned above.

What's new or changed:
- Added PCI detection.

Differences:
- 26A and 26D include the more standard, user-friendly boot sequence.
- 26B and 26C use a more technical boot screen for developers.
- 26A and 26B do not work due to the mention GRUB issue.
- 26C and 26D do work, however.

Testing
- These builds have been, mostly, tested.
- 26A and 26B both failed the successful boot test.
- 26C passed the basic function test.
