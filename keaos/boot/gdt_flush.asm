global gdt_flush

gdt_flush:
    mov eax, [esp+4]    ; pointer to gdt_ptr struct
    lgdt [eax]          ; load GDT

    ; Reload segment registers
    mov ax, 0x10        ; 0x10 = kernel data segment (entry 2)
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; Far jump to reload CS — MANDATORY after lgdt
    jmp 0x08:.done      ; 0x08 = kernel code segment (entry 1)
.done:
    ret