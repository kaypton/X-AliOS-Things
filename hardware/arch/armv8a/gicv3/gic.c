#include <k_api.h>

#include <sys/libkernel.h>
#include <sys/io.h>
#include <libfdt/libfdt.h>

#include <machine/gicv3.h>
#include <machine/reg.h>

#include <stdint.h>

uintptr_t gicv3_dist_base;
uint64_t gicv3_dist_size;

uintptr_t *gicv3_rdist_base;
uint64_t gicv3_rdist_size;
int gicv3_rdist_num;

static uintptr_t __gic_get_rdist(void)
{
    // TODO 根据当前 CPU ID 获取 Redistributor 的地址
    return gicv3_rdist_base[cpu_cur_get()];
}

static int __gic_wait_rwp(uint32_t intid)
{
    uint32_t rwp_mask;
    uintptr_t base;
    if(intid < GIC_SPI_INT_BASE)
    {
        base = __gic_get_rdist() + GICR_CTLR;
        rwp_mask = GICR_CTLR_RWP_MASK;
    } else {
        base = gicv3_dist_base;
        rwp_mask = GICD_CTLR_RWP_MASK;
    }

    while(readl(base) & rwp_mask);

    return 0;
}

static void __gicv3_rdist_enable(uintptr_t rdist)
{
    if(!(readl(rdist + GICR_WAKER) & GICR_WAKER_CA))
    {
        return;
    }

    clear_bit(rdist + GICR_WAKER, GICR_WAKER_PS_BIT);

    // wait for children wakeup 
    while(readl(rdist + GICR_WAKER) & GICR_WAKER_CA);
}

static void __gicv3_dist_init(void)
{
    uint32_t max_spi, intid, idx;

    uint32_t typer = readl(gicv3_dist_base + GICD_TYPER);
    
    max_spi = typer & GICD_TYPER_ITLINESNUM_MASK;
    max_spi = (max_spi + 1) << 5;

    /* disable the distributor */
    writel(0, gicv3_dist_base + GICD_CTLR);
    __gic_wait_rwp(GIC_SPI_INT_BASE);

#ifdef CONFIG_GIC_SINGLE_SECURITY_STATE 
    set_bit(gicv3_dist_base + GICD_CTLR, GICD_CTLR_DS_BIT);
    if(!test_bit(gicv3_dist_base + GICD_CTLR, GICD_CTLR_DS_BIT))
    {
        k_printf("Current GIC does not support single security state");
    }
#endif 

    for(intid = GIC_SPI_INT_BASE; intid < max_spi;
        intid += GIC_NUM_INTR_PER_REG)
    {
        idx = intid / GIC_NUM_INTR_PER_REG;
        /* Disable interrupt */
        writel(0xFFFFFFFFU, 
            (gicv3_dist_base + GICD_ICENABLER_n + idx * 4));

        /* Clear pending */
        writel(0xFFFFFFFFU,
            (gicv3_dist_base + GICD_ICPENDR_n + idx * 4));
        writel(0x0U,
            (gicv3_dist_base + GICD_IGROUPR_n + idx * 4));
        writel(0xFFFFFFFFU,
            (gicv3_dist_base + GICD_IGRPMODR_n + idx * 4));
    }

    __gic_wait_rwp(GIC_SPI_INT_BASE);

    for(intid = GIC_SPI_INT_BASE; intid < max_spi;
        intid += GIC_NUM_PRI_PER_REG)
    {
        writel(GIC_INT_DEF_PRI_X4, 
            (gicv3_dist_base + GICD_IPRIORITYR_n + intid));
    }

    for(intid = GIC_SPI_INT_BASE; intid < max_spi;
        intid += GIC_NUM_CFG_PER_REG)
    {
        idx = intid / GIC_NUM_CFG_PER_REG;
        writel(0, (gicv3_dist_base + GICD_ICFGR_n + idx * 4));
    }

#ifdef CONFIG_ARMV8_A_NS 
    writel((GICD_CTLR_ARE_NS | GICD_CTLR_ENABLE_G1NS),
        gicv3_dist_base + GICD_CTLR);
#elif defined(CONFIG_GIC_SINGLE_SECURITY_STATE)
    writel((GICD_CTLR_ARE_S | GICD_CTLR_ENABLE_G1NS), 
        gicv3_dist_base + GICD_CTLR);
#else
    set_bit(gicv3_dist_base + GICD_CTLR, GICD_CTLR_ENABLE_G1S_BIT);
#endif 

}

/*
 * Initialize the cpu interface. This should be called by each core.
 */
static void __gicv3_cpuif_init(void)
{
    uint32_t icc_sre, intid;

    uintptr_t base;
    
    /* SGI_base for controlling and generating PPIs and SGIs. */
    base = __gic_get_rdist() + 0x10000;
    /* Disable all sgi ppi */
    writel(0xFFFFFFFFU, base + GICR_SGI_BASE_ICENABLER0);
    /* Any sgi/ppi intid ie. 0-31 will select GICR_CTRL */
	__gic_wait_rwp(0);

    /* Clear pending */
	writel(0xFFFFFFFFU, base + GICR_SGI_BASE_ICPENDR0);

    /* Configure all SGIs/PPIs as G1S or G1NS depending on Zephyr
	 * is run in EL1S or EL1NS respectively.
	 * All interrupts will be delivered as irq
	 */
	writel(0x0U, base + GICR_SGI_BASE_IGROUPR0);
	writel(0xFFFFFFFFU, base + GICR_SGI_BASE_IGRPMODR0);

    /*
	 * Configure default priorities for SGI 0:15 and PPI 0:15.
	 */
    for(intid = 0; intid < GIC_SPI_INT_BASE;
        intid += GIC_NUM_PRI_PER_REG) {
        writel(GIC_INT_DEF_PRI_X4, base + GICR_SGI_BASE_IPRIORITYR + intid);
    }

    /* Configure PPIs as level triggered */
    writel(0, base + GICR_SGI_BASE_ICFGR1);

    /*
	 * Check if system interface can be enabled.
	 * 'icc_sre_el3' needs to be configured at 'EL3'
	 * to allow access to 'icc_sre_el1' at 'EL1'
	 */
    icc_sre = read_sysreg(ICC_SRE_EL1);

    if(!(icc_sre & ICC_SRE_ELx_SRE))
    {
        icc_sre = (icc_sre | ICC_SRE_ELx_SRE | ICC_SRE_ELx_DIB | ICC_SRE_ELx_DFB);
        write_sysreg(icc_sre, ICC_SRE_EL1);
        icc_sre = read_sysreg(ICC_SRE_EL1);

        // TODO log failed
        if(!(icc_sre & ICC_SRE_ELx_SRE)) 
            while(1);
    }

    write_sysreg(0xFF, ICC_PMR_EL1);

    /* Allow group1 interrupts */
    write_sysreg(1, ICC_IGRPEN1_EL1);
}

/*
    Both the Distributor and the CPU interfaces are disabled at reset. 
    The GIC must be initialized after reset 
    before it can deliver interrupts to the core.
*/
void gicv3_init(void)
{
    __gicv3_dist_init();

    // TODO set rdist base address for __gic_get_rdist()

    __gicv3_rdist_enable(__gic_get_rdist());
    __gicv3_cpuif_init();
}

void dt_gicv3_init(const void *fdt, int offset)
{
    int len, rdist_region_num, i, j, k, l, tmp, rdist_size;
    const struct fdt_property *fpp;
    fdt32_t *arr;
    int size_cells, address_cells;
    uintptr_t address;
    uint64_t size;

    fdt_get_property(fdt, offset, "interrupt-controller", &len);
    if(len == -FDT_ERR_NOTFOUND)
    {
        k_printf("[fdt] not gicv3 interrupt controller. gicv3 not initialized.\r\n");
        return;
    }

    size_cells = fdt_size_cells(fdt, offset);
    address_cells = fdt_address_cells(fdt, offset);

    // TODO We alloc the redistributor address array in 
    // the cpu init phase
    k_printf("gicv3 init.\r\n");
    k_printf("gic redistributor num: %d\r\n", gicv3_rdist_num);

    fpp = fdt_get_property(fdt, offset, "#redistributor-regions", &len);
    if(len < 0 && len == -FDT_ERR_NOTFOUND)
    {
        rdist_region_num = 1;
    } else if (len < 0) {
        k_printf("[fdt] something wrong.\r\n");
        k_printf("gicv3 not init.");
        return;
    } else {
        rdist_region_num = fdt32_to_cpu(*(fdt32_t *)fpp->data);
    }

    fpp = fdt_get_property(fdt, offset, "reg", &len);
    arr = (fdt32_t *)fpp->data;

    // TODO only support address-cells = 2 
    // TODO and size-cells = 2

    if(address_cells == 2)
    {
        gicv3_dist_base = fdt32_to_cpu(arr[1]);
        gicv3_dist_base += ((uintptr_t)fdt32_to_cpu(arr[0])) << 32;
    } else {
        k_printf("unsupport address cells: %d\r\n", address_cells);
    }
    
    if(size_cells == 2)
    {
        gicv3_dist_size = fdt32_to_cpu(arr[3]);
        gicv3_dist_base += ((uint64_t)fdt32_to_cpu(arr[2])) << 32;
    } else {
        k_printf("unsupport size cells: %d\r\n", size_cells);
    }

    arr += size_cells + address_cells;


    fpp = fdt_get_property(fdt, offset, "redistributor-stride", &len);
    if(len < 0 && len == -FDT_ERR_NOTFOUND)
    {
        rdist_size = 64 * 1024 * 2;
    } else if (len < 0) {
        k_printf("[fdt] something wrong.\r\n");
        k_printf("gicv3 not init.");
        return;
    } else {
        rdist_size = fdt32_to_cpu(*(fdt32_t *)fpp->data);
    }

    l = 0;
    for(i = rdist_region_num; i > 0;
        arr += size_cells + address_cells, i--)
    {   
        tmp = fdt32_to_cpu(arr[3]);
        tmp += ((uintptr_t)fdt32_to_cpu(arr[2])) << 32;

        k = tmp / rdist_size;

        address = fdt32_to_cpu(arr[1]);
        address += ((uintptr_t)fdt32_to_cpu(arr[0])) << 32;

        for(j = 0; j < k; j++)
        {
            gicv3_rdist_base[l] = address;
            address += rdist_size;
            l++;
        }
    }

    for(i = 0; i < gicv3_rdist_num; i++)
    {
        k_printf("gicv3 rdist %d address 0x%x. \r\n", i + 1, gicv3_rdist_base[i]);
    }   

    k_printf("gicv3 init done. \r\n");
}

