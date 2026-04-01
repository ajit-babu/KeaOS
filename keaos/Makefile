CC      := i686-elf-gcc
LD      := i686-elf-gcc
ASM     := nasm

CFLAGS  := -ffreestanding -O2 -Wall -Wextra -g
LDFLAGS := -ffreestanding -nostdlib -lgcc

KERNEL_C   := $(wildcard kernel/*.c)
KERNEL_OBJ := $(KERNEL_C:.c=.o)

BOOT_OBJ := boot/boot.o boot/gdt_flush.o boot/isr.o

OBJ := $(KERNEL_OBJ) $(BOOT_OBJ)

.PHONY: all run clean

all: keaos.iso

kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

boot/boot.o: boot/boot.asm
	$(ASM) -f elf32 $< -o $@

boot/gdt_flush.o: boot/gdt_flush.asm
	$(ASM) -f elf32 $< -o $@

boot/isr.o: boot/isr.asm
	$(ASM) -f elf32 $< -o $@

kernel.elf: $(OBJ)
	$(LD) -T linker.ld $(LDFLAGS) -o $@ $^
	@grub-file --is-x86-multiboot $@ && echo "✓ Multiboot OK"

keaos.iso: kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o keaos.iso iso/
	@echo "✓ ISO built"

run:
	unset LD_LIBRARY_PATH && env -i TERM=xterm PATH=/usr/bin:/bin qemu-system-i386 -cdrom keaos.iso -m 32M -display curses

clean:
	rm -f $(OBJ) kernel.elf keaos.iso