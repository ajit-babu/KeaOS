#include "gdt.h"

static gdt_entry_t gdt[3];
static gdt_ptr_t   gdt_ptr;

static void set_gate(int i, uint32_t base, uint32_t limit,
                      uint8_t access, uint8_t gran) {
    gdt[i].base_low  = base & 0xFFFF;
    gdt[i].base_mid  = (base >> 16) & 0xFF;
    gdt[i].base_high = (base >> 24) & 0xFF;
    gdt[i].limit_low = limit & 0xFFFF;
    gdt[i].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[i].access = access;
}

void gdt_init() {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base  = (uint32_t)&gdt;

    set_gate(0, 0, 0, 0, 0);               /* null descriptor */
    set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* kernel code */
    set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* kernel data */

    gdt_flush((uint32_t)&gdt_ptr);
}