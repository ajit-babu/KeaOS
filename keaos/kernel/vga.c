#include "vga.h"

#define VGA_MEM   ((volatile uint16_t*)0xB8000)
#define VGA_COLS  80
#define VGA_ROWS  25

static int          col = 0, row = 0;
static uint8_t     color = 0;

static uint8_t make_color(vga_color_t fg, vga_color_t bg) {
    return fg | (bg << 4);
}

void vga_set_color(vga_color_t fg, vga_color_t bg) {
    color = make_color(fg, bg);
}

static void scroll() {
    /* Move every row up one row */
    for (int r = 1; r < VGA_ROWS; r++)
        for (int c = 0; c < VGA_COLS; c++)
            VGA_MEM[(r-1)*VGA_COLS+c] = VGA_MEM[r*VGA_COLS+c];
    /* Clear last row */
    for (int c = 0; c < VGA_COLS; c++)
        VGA_MEM[(VGA_ROWS-1)*VGA_COLS+c] = ((uint16_t)color << 8) | ' ';
    row = VGA_ROWS - 1;
}

void vga_init() {
    vga_set_color(VGA_LGREEN, VGA_BLACK);
    /* Clear screen */
    for (int i = 0; i < VGA_ROWS * VGA_COLS; i++)
        VGA_MEM[i] = ((uint16_t)color << 8) | ' ';
    col = row = 0;
}

void kputchar(char c) {
    if (c == '\n') { col = 0; row++; }
    else if (c == '\r') { col = 0; }
    else if (c == '\b' && col > 0) {
        col--;
        VGA_MEM[row*VGA_COLS+col] = ((uint16_t)color << 8) | ' ';
        return;
    } else {
        VGA_MEM[row*VGA_COLS+col] = ((uint16_t)color << 8) | (uint8_t)c;
        col++;
    }
    if (col >= VGA_COLS) { col = 0; row++; }
    if (row >= VGA_ROWS) scroll();
}

void kprint(const char* s) { while (*s) kputchar(*s++); }

void kprint_hex(uint32_t n) {
    char buf[11]; buf[0]='0'; buf[1]='x'; buf[10]='\0';
    for (int i = 9; i >= 2; i--) {
        int d = n & 0xF;
        buf[i] = d < 10 ? '0'+d : 'a'+(d-10);
        n >>= 4;
    }
    kprint(buf);
}

void kprint_int(uint32_t n) {
    if (n == 0) { kputchar('0'); return; }
    char buf[12]; int i = 11; buf[i] = '\0';
    while (n > 0) { buf[--i] = '0' + (n % 10); n /= 10; }
    kprint(buf + i);
}