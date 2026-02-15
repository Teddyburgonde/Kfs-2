MBALIGN  equ  1 << 0				; Multiboot header
MEMINFO  equ  1 << 1
MBFLAGS  equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
	dd MAGIC
	dd MBFLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384							; 16 KiB stack
stack_top:

section .text
global _start:function (_start.end - _start)
extern main

_start:
	mov esp, stack_top
	call flush_gdt
	call main

	cli
	hlt
.hang:
	jmp .hang
.end:

section .gdt
gdt:
.null_descriptor:
	dq 0x0

; 8 bytes
.kernel_code:
	dq 0x00CF9A000000FFFF

.kernel_data:
	dq 0x00CF92000000FFFF  

.kernel_stack:
	dq 0x00CF92000000FFFF

.user_code:
	dq 0x00CFFA000000FFFF

.user_data:
	dq 0x00CFF2000000FFFF

.user_stack: 
	dq 0x00CFF2000000FFFF

gdt_end:

gdtr:
	dw gdt_end - gdt - 1 ; (limite size GDT at -1)
	dd gdt ; address gdt

flush_gdt:
    lgdt [gdtr]
    jmp 0x08:complete_flush
 
complete_flush:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret