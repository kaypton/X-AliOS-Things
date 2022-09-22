#include <machine/pt_regs.h>
#include <sys/types.h>

#define ASM_DEFINE_U64(sym, val) \
	asm volatile("\n.globl ASM_U64_" #sym "\nASM_U64_" #sym ":\n.long " " %0 \n" : : "i" (val))

void __section(".asm.data") asm_offset_main(void)
{
    ASM_DEFINE_U64(X0, offsetof(struct pt_regs, regs[0]));
    ASM_DEFINE_U64(PT_REGS_SIZE, sizeof(struct pt_regs));
}

#undef ASM_DEFINE_U64 






