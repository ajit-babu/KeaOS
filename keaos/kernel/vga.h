#pragma once
#include <stdint.h>

/* VGA color enum */
typedef enum {
    VGA_BLACK = 0,
    VGA_BLUE,
    VGA_GREEN,
    VGA_CYAN,
    VGA_RED,
    VGA_MAGENTA,
    VGA_BROWN,
    VGA_LIGHT_GREY,
    VGA_DARK_GREY,
    VGA_LBLUE,
    VGA_LGREEN,
    VGA_LCYAN,
    VGA_LRED,
    VGA_LMAGENTA,
    VGA_LBROWN,
    VGA_WHITE,
} vga_color_t;

/* VGA functions */
void vga_init();
void clear_screen();
void vga_set_color(vga_color_t fg, vga_color_t bg);

void kprint(const char *str);
void kprint_hex(uint32_t n);
void kprint_int(uint32_t n);