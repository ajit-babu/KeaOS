#include <stdint.h>
#include "vga.h"
#include "gdt.h"

void kernel_main(uint32_t magic, uint32_t mboot_addr){
    (void)mboot_addr;

    gdt_init();        // ✅ MUST BE FIRST
    vga_init();        // then initialize display

    kprint("  _  __             ___  ____\n");
    kprint(" | |/ /___  __ _  / _ \\/ ___|\n");
    kprint(" | ' // _ \\/ _` || | | \\___ \\\n");
    kprint(" | . \\  __/ (_| || |_| |___) |\n");
    kprint(" |_|\\_\\___|\\__,_| \\___/|____/\n\n");

    kprint(" KeaOS v0.1 -- Intelligent Foundation\n");
    kprint(" Multiboot magic: ");
    kprint_hex(magic);
    kprint("\n");

    kprint(" GDT Initialized Successfully\n");
    kprint(" Status: Kernel loaded OK\n");

    for (;;) __asm__ volatile("hlt");
}