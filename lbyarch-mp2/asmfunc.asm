section .data
msg db "Hello World",13,10,0

section .text
bits 64
default rel ; to handle address relocation

global asm_dot_product
extern printf

asm_dot_product:
	sub rsp, 8*5 ; caller
	lea rcx, [msg]
	call printf
	add rsp, 8*5
	ret
