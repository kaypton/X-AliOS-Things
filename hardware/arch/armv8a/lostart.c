#include <machine/reg.h>
#include <machine/gtimer.h>
#include <machine/gicv3.h>
#include <machine/io.h>

#include <libfdt/libfdt.h>

#include <string.h>

#include <sys/libkernel.h>

#include <k_api.h>

void pl011_reset(void);
void pl011_putc(char c);
void pl011_puts(const char *s);

struct stdout_ops _stdout_ops = {
    .putc = pl011_putc
};

struct stdout_ops *stdout_ops = &_stdout_ops;

void cpu_initclock(void)
{
    gtimer_init();
}

void earlycon_init(void)
{
    pl011_reset();
}

extern uintptr_t *gicv3_rdist_base;
extern int gicv3_rdist_num;

void dt_cpu_init(const char *fdt)
{
    int poff, len, size_cells, address_cells;
    int subnode_off, cpu_num = 0;
    const char *pbuf;
    struct fdt_property *fpp;

    int node_offset = fdt_subnode_offset(fdt, 0, "cpus");

#define CPU_INIT_PRT "[cpu-init] "

    k_printf(CPU_INIT_PRT"cpu init. \r\n");

    size_cells = fdt_size_cells(fdt, node_offset);
    address_cells = fdt_address_cells(fdt, node_offset);

    fdt_for_each_subnode(subnode_off, fdt, node_offset)
    {
        fpp = fdt_get_property(fdt, subnode_off, "device_type", &len);
        if(!strcmp(fpp->data, "cpu"))
            cpu_num++;
    }

    k_printf(CPU_INIT_PRT"cpu num %d\r\n", cpu_num);

    gicv3_rdist_base = krhino_mm_alloc(sizeof(uintptr_t) * cpu_num);
    gicv3_rdist_num = cpu_num;

#undef CPU_INIT_PRT
}

void irq_enable(void)
{
    __asm__ volatile (
        "msr daifclr, #2"
        :
        :
        : "memory"
    );
}

void irq_disable(void)
{
    __asm__ volatile (
        "msr daifset, #2"
        :
        :
        : "memory"
    );
}

const void *fdt_base = (void *)0x40000000;

static void walk_dt()
{
    int subnode_off, len;

    subnode_off = fdt_first_subnode(fdt_base, 0);

    fdt_for_each_subnode(subnode_off, fdt_base, 0)
    {

        if(!fdt_node_check_compatible(fdt_base, subnode_off, "arm,gic-v3"))
            dt_gicv3_init(fdt_base, subnode_off);

        subnode_off = fdt_next_subnode(fdt_base, subnode_off);
    }
}



void lostart(void)
{
    earlycon_init();
    cpu_initclock();

    krhino_init();

    k_printf("arm64 wake up\r\n");

    arm64_mpidr_t mpidr = read_mpidr_el1();

    k_printf("[lostart] cpu mpidr 0x%x \r\n", mpidr);

    dt_cpu_init(fdt_base);

    walk_dt();
    /* never run here */
    while(1)
    {
        gtimer_delays(1);
        k_printf("wait for one second\r\n");
    }
}

void secondary_lostart(void)
{
    // TODO 
}


