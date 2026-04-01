#include <stdint.h>
#include "vga.h"
#include "gdt.h"
#include "idt.h"   // ✅ REQUIRED

void kernel_main(uint32_t magic, uint32_t mboot_addr){
    (void)mboot_addr;

    gdt_init();        // MUST be first
    vga_init();
    idt_init();        // Enable interrupts

    kprint("  _  __             ___  ____\n");
    kprint(" | |/ /___  __ _  / _ \\/ ___|\n");
    kprint(" | ' // _ \\/ _` || | | \\___ \\\n");
    kprint(" | . \\  __/ (_| || |_| |___) |\n");
    kprint(" |_|\\_\\___|\\__,_| \\___/|____/\n\n");

    kprint(" KeaOS v0.2 -- Interrupts Enabled\n");

    kprint(" Multiboot magic: ");
    kprint_hex(magic);
    kprint("\n");

    kprint(" GDT Initialized Successfully\n");
    kprint(" Status: Kernel loaded OK\n");
    kprint(" Type on keyboard: \n");

    while (1) {
        __asm__ volatile("hlt");  // ✅ correct usage in loop
    }
}