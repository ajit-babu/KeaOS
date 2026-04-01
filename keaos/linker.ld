/* KeaOS Linker Script
   Loads kernel at 1MB (0x00100000) — standard for Multiboot kernels */

ENTRY(_start)   /* entry point matches _start in boot.asm */

SECTIONS {
    /* Start at 1MB physical address */
    . = 0x00100000;

    /* Multiboot header MUST come first */
    .multiboot : {
        *(.multiboot)
    }

    /* Executable code */
    .text ALIGN(4K) : {
        *(.text)
        *(.text.*)
    }

    /* Read-only data (string literals, const) */
    .rodata ALIGN(4K) : {
        *(.rodata)
        *(.rodata.*)
    }

    /* Initialised data */
    .data ALIGN(4K) : {
        *(.data)
    }

    /* Zero-initialised data (stack lives here) */
    .bss ALIGN(4K) : {
        *(COMMON)
        *(.bss)
    }

    /* Export kernel end address for allocator */
    kernel_end = .;
}