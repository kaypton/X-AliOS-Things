#ifndef __GTIMER_H__
#define __GTIMER_H__

unsigned long long gtimer_get_phy_counter_value(void);
unsigned long long gtimer_get_system_counter_freq(void);
void gtimer_init(void);
void gtimer_delays(int s);
void gtimer_delayms(int ms);

#endif 

