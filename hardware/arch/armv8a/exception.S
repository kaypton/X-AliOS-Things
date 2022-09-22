/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, DiShi Xu
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
    .arch armv8-a 

    .macro exception_save_register

    sub sp, sp, #256  /* 16 * 16 */

    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]

    mrs x10, elr_el1 
    mrs x11, spsr_el1 
    mrs x12, esr_el1 

    stp x10, x11, [sp, #16 * 15]
    stp x12, x30, [sp, #16 * 16]

    .endm 

    .macro exception_restore_register

    ldp x10, x11, [sp, #16 * 15]
    ldp x12, x30, [sp, #16 * 16]

    msr elr_el1, x10 
    msr spsr_el1, x11 
    msr esr_el1, x12 

    ldp x0, x1, [sp, #16 * 0]
    ldp x2, x3, [sp, #16 * 1]
    ldp x4, x5, [sp, #16 * 2]
    ldp x6, x7, [sp, #16 * 3]
    ldp x8, x9, [sp, #16 * 4]
    ldp x10, x11, [sp, #16 * 5]
    ldp x12, x13, [sp, #16 * 6]
    ldp x14, x15, [sp, #16 * 7]
    ldp x16, x17, [sp, #16 * 8]
    ldp x18, x19, [sp, #16 * 9]
    ldp x20, x21, [sp, #16 * 10]
    ldp x22, x23, [sp, #16 * 11]
    ldp x24, x25, [sp, #16 * 12]
    ldp x26, x27, [sp, #16 * 13]
    ldp x28, x29, [sp, #16 * 14]

    add sp, sp, #256 /* 16 * 16 */

    .endm 
    
    .macro vector_entry el, ht, regsize, label 
    .align 7
entry_start_\@:
    exception_save_register 
    bl el\el\ht\()_\regsize\()_\label 
    exception_restore_register 
    eret 
    .endm 

    .pushsection ".el1vector.text", "ax"
    .globl el1_vectors 
    .align 11
el1_vectors:

    vector_entry 1, t, 64, sync 
    vector_entry 1, t, 64, irq 
    vector_entry 1, t, 64, fiq 
    vector_entry 1, t, 64, error 

    vector_entry 1, h, 64, sync 
    vector_entry 1, h, 64, irq 
    vector_entry 1, h, 64, fiq 
    vector_entry 1, h, 64, error 

    vector_entry 0, t, 64, sync 
    vector_entry 0, t, 64, irq 
    vector_entry 0, t, 64, fiq 
    vector_entry 0, t, 64, error 

    vector_entry 0, t, 32, sync 
    vector_entry 0, t, 32, irq 
    vector_entry 0, t, 32, fiq 
    vector_entry 0, t, 32, error 
    .popsection

