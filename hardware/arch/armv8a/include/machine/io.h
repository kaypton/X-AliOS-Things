#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>
#include <sys/cdefs.h>

#ifndef __ASM__
#define DMB	asm volatile ("dmb sy" : : : "memory")

#define dmb()	DMB

#define __iormb() dmb()
#define __iowmb() dmb()

#define __arch_getb(a) (*(volatile unsigned char *)(a))
#define __arch_getw(a) (*(volatile unsigned short *)(a))
#define __arch_getl(a) (*(volatile unsigned int *)(a))
#define __arch_getq(a) (*(volatile unsigned long long *)(a))

#define __arch_putb(v, a) (*(volatile unsigned char *)(a) = (v))
#define __arch_putw(v, a) (*(volatile unsigned short *)(a) = (v))
#define __arch_putl(v, a) (*(volatile unsigned int *)(a) = (v))
#define __arch_putq(v, a) (*(volatile unsigned long long *)(a) = (v))

#define writeb(v, c)                                                           \
	({                                                                     \
		uint8_t __v = v;                                                    \
		__iowmb();                                                     \
		__arch_putb(__v, c);                                           \
		__v;                                                           \
	})
#define writew(v, c)                                                           \
	({                                                                     \
		uint16_t __v = v;                                                   \
		__iowmb();                                                     \
		__arch_putw(__v, c);                                           \
		__v;                                                           \
	})
#define writel(v, c)                                                           \
	({                                                                     \
		uint32_t __v = v;                                                   \
		__iowmb();                                                     \
		__arch_putl(__v, c);                                           \
		__v;                                                           \
	})
#define writeq(v, c)                                                           \
	({                                                                     \
		uint64_t __v = v;                                                   \
		__iowmb();                                                     \
		__arch_putq(__v, c);                                           \
		__v;                                                           \
	})

#define readb(c)                                                               \
	({                                                                     \
		uint8_t __v = __arch_getb(c);                                       \
		__iormb();                                                     \
		__v;                                                           \
	})
#define readw(c)                                                               \
	({                                                                     \
		uint16_t __v = __arch_getw(c);                                      \
		__iormb();                                                     \
		__v;                                                           \
	})
#define readl(c)                                                               \
	({                                                                     \
		uint32_t __v = __arch_getl(c);                                      \
		__iormb();                                                     \
		__v;                                                           \
	})
#define readq(c)                                                               \
	({                                                                     \
		uint64_t __v = __arch_getq(c);                                      \
		__iormb();                                                     \
		__v;                                                           \
	})

static __always_inline inline void set_bit(uintptr_t addr, unsigned int bit)
{
	uint32_t temp = *(volatile uint32_t *)addr;
	*(volatile uint32_t *)addr = temp | (1 << bit);
}

static __always_inline inline void clear_bit(uintptr_t addr, unsigned int bit)
{
	uint32_t temp = *(volatile uint32_t *)addr;

	*(volatile uint32_t *)addr = temp & ~(1 << bit);
}

static __always_inline inline int test_bit(uintptr_t addr, unsigned int bit)
{
	uint32_t temp = *(volatile uint32_t *)addr;
	return temp & (1 << bit);
}

#define STRINGIFY(s) #s

#define read_sysreg(reg)						\
({									\
	uint64_t val;							\
	asm volatile ("mrs %0, " STRINGIFY(reg)			\
			  : "=r" (val) :: "memory");			\
	val;								\
})

#define write_sysreg(val, reg)						\
({									\
	asm volatile ("msr " STRINGIFY(reg) ", %0"			\
			  :: "r" (val) : "memory");			\
})

#define zero_sysreg(reg)						\
({									\
	asm volatile ("msr " STRINGIFY(reg) ", xzr"			\
			  ::: "memory");				\
})

#define RWZ_SYSREG_HELPER(reg)						\
	static __always_inline inline uint64_t read_##reg(void)			\
	{								\
		return read_sysreg(reg);				\
	}								\
	static __always_inline inline void write_##reg(uint64_t val)		\
	{								\
		write_sysreg(val, reg);					\
	}								\
	static __always_inline inline void zero_##reg(void)			\
	{								\
		zero_sysreg(reg);					\
	}

RWZ_SYSREG_HELPER(mpidr_el1);

#define BIT(n) (1UL << (n))
#define BIT64(n) (1ULL << (n))

#define BIT_MASK(n) (BIT(n) - 1UL)
#define BIT64_MASK(n) (BIT64(n) - 1ULL)

typedef uint64_t arm64_mpidr_t;

#endif  /* #ifndef __ASM__ */



#endif 

