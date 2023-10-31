NanamiOS Version 1.0 [Codename: "Reimu"] Build 15

System Requirements:
- CD drive
- Intel i386 or better (Pentium 4 recommended)
- 64 megabytes of RAM
- 4 GB hard drive
- A display

Warnings:
- Only one driver is provided in this version. It is very primitive and has almost no driver support, apart from a primitive keyboard driver.
- If you want to run this on physical hardware, do so at your own risk. Nothing should go wrong, but I recommend you boot off of a CD.

Known Issues:
- Command Line doesn't exist.
- Only one driver exists.
- The keyboard driver is very primitive and only takes very strict input. The following text is a sample provided by me on Linux emulating the driver:

          -- TESTING111 --
               I MADE THIS DRIVER TODAY 9OVER THE COURSE OF SIX HOURS0.
          IT IS VERY PRIMTIVE 9HOW DID I NOT MESS UP, THAT'S WHAT I WANTED TO DO111 .-,0.
          I CALLED IT 'NANAMIKEYBOARD' 9UGH, AGAIN... .-,0, AND IT'S DESIGNED FOR NANAMIOS.
          LET'S ME -- AHH, THERE WE GO111 I CAN'T MAKE A BACKSPACE, AS IT'S NOT RECOGNIZED BY THE
          DRIVER... YET.

          WELL, IT SHOULD BE HANDY FOR NOTE-TAKING, AND SHOUD-- SHOULD!! 9UGH...0 PROVIDE A CHALLENGE IN
          NOT MAKING TYPOS.

          -- END OF TESTING111 --

- Any keys not picked up by the driver will cause an "          xx    unrecognized key" issue.

Patch Notes:
- Nothing!

What's new or changed:
- Added responses for most general-use keys.
- Added an F1 key macro-command displaying driver and OS version info.

Testing
- This build has been Working Features Test.
- This build has passed the Basic Reliability Test.
