extern kernel_main
; KeaOS Bootloader Entry — Multiboot Compliant
; GRUB reads the magic header and jumps to _start

bits 32

; ── Multiboot header constants ──
MBOOT_MAGIC    equ 0x1BADB002
MBOOT_ALIGN    equ 1 << 0         ; align modules on 4KB
MBOOT_MEMINFO  equ 1 << 1         ; request memory map
MBOOT_FLAGS    equ MBOOT_ALIGN | MBOOT_MEMINFO
MBOOT_CHECKSUM equ -(MBOOT_MAGIC + MBOOT_FLAGS)

; ── Multiboot header (must be in first 8KB of kernel) ──
section .multiboot
align 4
  dd MBOOT_MAGIC
  dd MBOOT_FLAGS
  dd MBOOT_CHECKSUM

; ── BSS section for kernel stack ──
section .bss
align 16
stack_bottom:
  resb 16384          ; 16 KB kernel stack
stack_top:

; ── Entry point ──
section .text
global _start
_start:
  ; GRUB puts magic in EAX, multiboot_info* in EBX
  ; Save them before we touch any registers
  mov  esp, stack_top     ; set up our stack
  push ebx               ; pass multiboot_info to kernel
  push eax               ; pass magic number to kernel
  call kernel_main       ; jump into C!

.hang:
  cli                    ; disable interrupts
  hlt                    ; halt CPU
  jmp .hang              ; if somehow we wake, halt again