#include <machine/gtimer.h>
#include <machine/io.h>

static uint64_t scf;

void gtimer_enable_interrupt(void)
{
    
}


void gtimer_init(void)
{
    write_cntp_ctl_el0(1);
    write_cntp_tval_el0(1);

    scf = read_cntfrq_el0();
}

void gtimer_delayms(int ms)
{
    uint64_t tmp, i = read_cntpct_el0();
    
    for(;;)
    {
        tmp = read_cntpct_el0();
        if(tmp >= i + ms * (scf / 1000))
            break;
    }
}

void gtimer_delays(int s)
{
    gtimer_delayms(s * 1000);
}


