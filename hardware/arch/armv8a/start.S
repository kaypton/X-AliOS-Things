#include <machine/reg.h>

#define TCB_SIZE 0x0
#define CONFIG_INIT_STACK_SIZE 10

    .macro asm_get_u64 reg, name, regsize, label 
    adrp \reg\(),ASM_U64_\name
    add \reg\(), \reg\(), :lo12:ASM_U64_\name
    ldr \reg\(), [\reg\()]
    and \reg\(), \reg\(), #0xFFFFFFFF
    .endm 

/*
 * startup stage 1
 * mmu=off D/I-cache=off 
 * Exception level = el2 / el1 
 *
 * we will drop to el1 and clean the bss section
 * and setup early init stack for early C environment 
 * then jump to startup stage 2
 */
    .arch armv8-a
	.section ".init.head", "ax"

    .align 2
	.globl _start0
_start0:	

    mov x0, xzr
	ldr x1, =__image_end__ 
	ldr x3, =__image_start__ 
    sub x1, x1, x3 
    isb 

.Lreloc:
	ldr x2, [x0], #8
	str x2, [x3], #8

    cmp x0, x1
    
	b.lo .Lreloc

    ldr x0, =_start 
    br x0 

    .align 2
_start:
    
    mrs x20, CurrentEL  /* get current exception level */
	lsr x20, x20, #2  

	cmp x20, #2    
	b.eq _el2_entry

	cmp x20, #1
	b.eq _el1_entry

    b halt 
	
	.align 2
_el2_entry:

    
    ldr x2, =0x000033ff
	msr cptr_el2, x2

    msr hstr_el2, xzr 

    mrs x2, cnthctl_el2
	orr x2, x2, #(CNTHCTL_EL1PCTEN | CNTHCTL_EL1PCEN)
	msr cnthctl_el2, x2

	msr cntvoff_el2, xzr

	msr sctlr_el1, xzr
	mrs x0, hcr_el2
	orr x0, x0, #(1 << 31)  /* EL1 Execution state is AArch64 */
	msr hcr_el2, x0
	mov x0, #(PSR_M_EL1h | PSR_DAIF)
	msr spsr_el2, x0

	adrp x0, _start
	add x0, x0, :lo12:_start
	msr elr_el2, x0
	isb 
	eret
	
	.align 2
_el1_entry:
	
    /*
     * now we are in EL1
     */ 

    /* clear bss */
    ldr x15, =__bss_start__
    ldr x14, =__bss_end__
1:
    str xzr, [x15], #8
    cmp x15, x14 
    b.lo 1b

    /* setup init stack */
    adrp x0, _init_stack_top 
    add x0, x0, :lo12:_init_stack_top
    mov sp, x0

    asm_get_u64 x0 PT_REGS_SIZE
    sub sp, sp, x0 
    
    /* setup vectors */
    adrp x0, el1_vectors
    add x0, x0, :lo12:el1_vectors 
    msr vbar_el1, x0 

    /* go into startup stage 2 */
    b lostart

    .align 2
halt:
    b halt

    .section ".init.stack", "aw"
    .align 4
_init_stack:
    .space 4096 * CONFIG_INIT_STACK_SIZE
_init_stack_top:




