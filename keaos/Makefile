# KeaOS Makefile
CC      := i686-elf-gcc
LD      := i686-elf-gcc
ASM     := nasm

CFLAGS  := -ffreestanding -O2 -Wall -Wextra -g
LDFLAGS := -ffreestanding -nostdlib -lgcc

# Source files
KERNEL_C   := $(wildcard kernel/*.c)
KERNEL_OBJ := $(KERNEL_C:.c=.o)

BOOT_OBJ   := boot/boot.o boot/gdt_flush.o

OBJ := $(KERNEL_OBJ) $(BOOT_OBJ)

.PHONY: all run clean iso debug

all: keaos.iso

# Compile C files
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble boot files
boot/boot.o: boot/boot.asm
	$(ASM) -f elf32 $< -o $@

boot/gdt_flush.o: boot/gdt_flush.asm
	$(ASM) -f elf32 $< -o $@

# Link kernel
kernel.elf: $(OBJ)
	$(LD) -T linker.ld $(LDFLAGS) -o $@ $^
	@grub-file --is-x86-multiboot $@ && echo "✓ Multiboot OK" || echo "✗ Multiboot FAIL"

# Build ISO
keaos.iso: kernel.elf
	mkdir -p iso/boot/grub
	cp kernel.elf iso/boot/kernel.elf
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o keaos.iso iso/
	@echo "✓ ISO built: keaos.iso"

# Run (safe mode without GTK issues)
run: keaos.iso
	unset LD_LIBRARY_PATH && env -i PATH=/usr/bin:/bin qemu-system-i386 -cdrom keaos.iso -m 32M -display curses

# Debug mode
debug: keaos.iso
	qemu-system-i386 -cdrom keaos.iso -m 32M -s -S

# Clean build
clean:
	rm -f $(OBJ) kernel.elf keaos.iso iso/boot/kernel.elf