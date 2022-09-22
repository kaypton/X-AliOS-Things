    .globl cpu_intrpt_save
    .globl cpu_intrpt_restore
    .globl cpu_intrpt_switch
    .globl cpu_first_task_start

    .globl cpu_switch_to 


    .text 
    .align 2 
cpu_intrpt_save:
    ret 

cpu_intrpt_restore:
    ret 

cpu_intrpt_switch:
    ret 

cpu_switch_to:
    /* src task store */
    ldr x8, [x0] 
    mov x9, sp 

    stp x19, x20, [x8], #16
    stp x21, x22, [x8], #16
    stp x23, x24, [x8], #16
    stp x25, x26, [x8], #16
    stp x27, x28, [x8], #16
    stp x29, x9, [x8], #16
    str lr, [x8]

    /* dest task restore */
    ldr x8, [x1]
	ldp	x19, x20, [x8], #16		// restore callee-saved registers
	ldp	x21, x22, [x8], #16
	ldp	x23, x24, [x8], #16
	ldp	x25, x26, [x8], #16
	ldp	x27, x28, [x8], #16
	ldp	x29, x9, [x8], #16
	ldr	lr, [x8]
	mov	sp, x9

    ret 


cpu_first_task_start:
    ret 



