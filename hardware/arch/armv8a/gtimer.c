#include <machine/gtimer.h>
#include <machine/io.h>

static unsigned long long system_counter_freq;

unsigned long long gtimer_get_phy_counter_value()
{
    unsigned long long ret;
    __asm__(
        "mrs x20, cntpct_el0\n"
        "mov %0, x20"
        : "=r"(ret)
    );
    return ret;
}

unsigned long long gtimer_get_system_counter_freq()
{
    unsigned long long ret;
    __asm__(
        "mrs x20, cntfrq_el0\n"
        "mov %0, x20"
        : "=r"(ret)
    );
    return ret;
}

void gtimer_enable_interrupt(void)
{
    
}


void gtimer_init(void)
{
    asm volatile (
        "mov x0, #1 \n"
        "msr cntp_ctl_el0, x0"
        :
        :
        : "memory"
    );

    asm volatile(
        "msr cntp_tval_el0, %[timer_val]"
        :
        : [timer_val] "r" (1)
        : "memory"
    );

    system_counter_freq = gtimer_get_system_counter_freq();
}

void gtimer_delayms(int ms)
{
    unsigned long long tmp, i = gtimer_get_phy_counter_value();
    
    for(;;)
    {
        tmp = gtimer_get_phy_counter_value();
        if(tmp >= i + ms * (system_counter_freq / 1000))
            break;
    }
}

void gtimer_delays(int s)
{
    gtimer_delayms(s * 1000);
}


