#include "vga.h"
#include <stdint.h>

/* Simple keymap */
static const char keymap[128] = {
    0,27,'1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/',
    0,'*',0,' ',
};

static inline uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void keyboard_handler() {
    uint8_t sc = inb(0x60);

    if (!(sc & 0x80)) {
        char c = keymap[sc];
        if (c) {
            char str[2] = {c, 0};
            kprint(str);
        }
    }

    outb(0x20, 0x20); // EOI
}