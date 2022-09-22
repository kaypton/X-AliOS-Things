	.arch armv8-a
	.file	"asm-offset.c"
	.text
	.section	.asm.data,"ax",@progbits
	.align	2
	.global	asm_offset_main
	.type	asm_offset_main, %function
asm_offset_main:
.LFB0:
	.cfi_startproc
#APP
// 9 "asm-offset.c" 1
	
.globl ASM_U64_X0
ASM_U64_X0:
.long  0 

// 0 "" 2
// 10 "asm-offset.c" 1
	
.globl ASM_U64_PT_REGS_SIZE
ASM_U64_PT_REGS_SIZE:
.long  272 

// 0 "" 2
#NO_APP
	nop
	ret
	.cfi_endproc
.LFE0:
	.size	asm_offset_main, .-asm_offset_main
	.ident	"GCC: (GNU) 11.3.1 20220421 (Red Hat 11.3.1-2)"
	.section	.note.GNU-stack,"",@progbits
