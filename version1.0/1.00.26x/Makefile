
GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -Wno-write-strings
ASPARAMS = --32
LDPARAMS = -melf_i386

objects = src._.loader.o \
 src._.gdt.o \
 src.drivers.driver.o \
 src.hwcom.port.o \
 src.hwcom.interruptstubs.o \
 src.hwcom.interrupts.o \
 src.hwcom.pci.o \
 src.drivers.keyboard.o \
 src.drivers.mouse.o \
 src._.kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) -o $@ -c $<
	
%.o: %.s
	as $(ASPARAMS) -o $@ $< 
	
sphxkskernel.bin: linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)


install: sphxkskernel.bin
	sudo cp $< /boot/shpxkskernel.bin


nanami_os.iso: sphxkskernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	cp $< iso/boot/
	echo 'set timeout=0' > iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "NanamiOS 1.00 Build 26 [2023 November 7th on S-PHXKS kernel]" {' >> iso/boot/grub/grub.cfg
	echo '  multiboot /boot/sphxkskernel.bin' >> iso/boot/grub/grub.cfg
	echo '  boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	grub-mkrescue --output=$@ iso
	rm -rf iso


.PHONY: clean
clean:
	rm -f $(objects) sphxkskernel.bin nanami_os.iso