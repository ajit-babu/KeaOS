# KeaOS Makefile
CC      := i686-elf-gcc
LD      := i686-elf-gcc
ASM     := nasm
CFLAGS  := -ffreestanding -O2 -Wall -Wextra -g
LDFLAGS := -ffreestanding -nostdlib -lgcc

KERNEL_C   := $(wildcard kernel/*.c)
KERNEL_OBJ := $(KERNEL_C:.c=.o) boot/boot.o

.PHONY: all run clean iso

all: keaos.iso

# Compile each .c file
kernel/%.o: kernel/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble boot.asm
boot/boot.o: boot/boot.asm
	$(ASM) -f elf32 $< -o $@

# Link everything into kernel ELF
kernel.elf: $(KERNEL_OBJ)
	$(LD) -T linker.ld $(LDFLAGS) -o $@ $^
	@grub-file --is-x86-multiboot $@ && echo "✓ Multiboot OK" || echo "✗ Multiboot FAIL"

# Build bootable ISO
keaos.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o keaos.iso iso/ 2>/dev/null
	@echo "✓ ISO built: keaos.iso"

# Boot in QEMU
run: keaos.iso
	qemu-system-i386 -cdrom keaos.iso -m 32M

# Debug mode — attach GDB on port 1234
debug: keaos.iso
	qemu-system-i386 -cdrom keaos.iso -m 32M -s -S &

clean:
	rm -f $(KERNEL_OBJ) kernel.elf keaos.iso iso/boot/kernel.elf