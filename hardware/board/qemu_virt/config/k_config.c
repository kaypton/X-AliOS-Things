#include <k_api.h>

#include <stdint.h>

extern void *_init_heap;
extern void *_init_heap_top;

k_mm_region_t g_mm_region[1] = {
    {
        .start = (uint8_t *)&_init_heap,
        .len = 0x6400000
    }
};
int g_region_num = 1;
krhino_err_proc_t g_err_proc = soc_err_proc;

hr_timer_t soc_hr_hw_cnt_get(void)
{
    return 0;
}

lr_timer_t soc_lr_hw_cnt_get(void)
{
    return 0;
}

void soc_err_proc(kstat_t err)
{
}

void krhino_tick_hook(void)
{
}

void krhino_sleep(void)
{
}

void krhino_idle_hook(void)
{
}

void krhino_idle_pre_hook(void)
{ 
}

void krhino_start_hook(void)
{
}

void krhino_task_create_hook(ktask_t *task)
{
}

void krhino_task_del_hook(ktask_t *task, res_free_t *arg)
{
}

void krhino_init_hook(void)
{
}

void krhino_task_switch_hook(ktask_t *orgin, ktask_t *dest)
{
}

void krhino_mm_alloc_hook(void *mem, size_t size)
{
}

void krhino_task_abort_hook(ktask_t *task)
{
}

