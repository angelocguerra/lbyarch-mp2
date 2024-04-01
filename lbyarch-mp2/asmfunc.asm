section .text
bits 64
default rel ; to handle address relocation

global asm_dot_product
extern printf

;Performs a dot product between 2 vectors (x86_64 Assembly Version)
; Params:
; RCX - n
; RDX - vectorA
; R8 - vectorB
; Returns XMM0 (sdot)
asm_dot_product:
	PUSH RBX ; initialize counter (i)
	XOR RBX, RBX ; reset counter to 0
	XORPS XMM0, XMM0 ; reset reg

	SUMMATION:
		MOVSS XMM1, dword[RDX + RBX * 4] ; Initialize with multiplicand
		MULSS XMM1, dword[R8 + RBX * 4] ; Multiply to multiplier
		ADDSS XMM0, XMM1 ; Save product to reg

		INC RBX ; Increment counter
		CMP RBX, RCX ; If i==n
		JZ END_SUMMATION ; End loop

		JMP SUMMATION ; Else proceed to next iteration

	END_SUMMATION:
		POP RBX ; clear counter
		ret