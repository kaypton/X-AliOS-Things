#ifndef __GICV3_H__
#define __GICV3_H__

/* GIC Distributor Registers offset */
#define GICD_CTLR    (0x0000U)
#define GICD_TYPER   (0x0004U)
#define GICD_IIDR    (0x0008U)
#define GICD_STATUSR (0x0010U)
#define GICD_SETSPI_NSR    (0x0040U)
#define GICD_CLRSPI_NSR    (0x0048U)
#define GICD_SETSPI_SR     (0x0050U)
#define GICD_CLRSPI_SR     (0x0058U)
#define GICD_IGROUPR_n     (0x0080U)
#define GICD_ISENABLER_n   (0x0100U)
#define GICD_ICENABLER_n   (0x0180U)
#define GICD_ISPENDR_n     (0x0200U)
#define GICD_ICPENDR_n     (0x0280U)
#define GICD_ISACTIVER_n   (0x0300U)
#define GICD_ICACTIVER_n   (0x0380U)
#define GICD_IPRIORITYR_n  (0x0400U)
#define GICD_ITARGETSR_n   (0x0800U)
#define GICD_ICFGR_n       (0x0C00U)
#define GICD_IGRPMODR_n    (0x0D00U)
#define GICD_NSACR_n       (0x0E00U)
#define GICD_SGIR          (0x0F00U)
#define GICD_CPENDSGIR_n   (0x0F10U)
#define GICD_SPENDSGIR_n   (0x0F20U)
#define GICD_IROUTER_n     (0x6100U)

/* GIC Redistributor Registers offset */
#define GICR_CTLR    (0x0000U)
#define GICR_IIDR    (0x0004U)
#define GICR_TYPER   (0x0008U)
#define GICR_STATUSR (0x0010U)
#define GICR_WAKER   (0x0014U)
#define GICR_SETLPIR (0x0040U)
#define GICR_CLRLPIR (0x0048U)
#define GICR_PROPBASER    (0x0070U)
#define GICR_PENDBASER    (0x0078U)
#define GICR_INVLPIR (0x00A0U)
#define GICR_INVALLR (0x00B0U)
#define GICR_SYNCR   (0x00C0U)
#define GICR_VPROPBASER   (0x0070U)
#define GICR_VPENDBASER   (0x0078U)
#define GICR_IGROUPR0     (0x0080U)
#define GICR_ISENABLER0   (0x0100U)
#define GICR_ICENABLER0   (0x0180U)
#define GICR_ISPENDR0     (0x0200U)
#define GICR_ICPENDR0     (0x0280U)
#define GICR_ISACTIVER0   (0x0300U)
#define GICR_ICACTIVER0   (0x0380U)
#define GICR_IPRIORITYR_n (0x0400U)
#define GICR_ICFGR0   (0x0C00U)
#define GICR_ICFGR1   (0x0C04U)
#define GICR_IGRPMODR0    (0x0D00U)
#define GICR_NSACR    (0x0E00U)

/* GIC Redistributor SGI_base Registers offset */
#define GICR_SGI_BASE_IGROUPR0    (0x0080U)
#define GICR_SGI_BASE_ISENABLER0  (0x0100U)
#define GICR_SGI_BASE_ICENABLER0  (0x0180U)
#define GICR_SGI_BASE_ISPENDR0    (0x0200U)
#define GICR_SGI_BASE_ICPENDR0    (0x0280U)
#define GICR_SGI_BASE_ISACTIVER0  (0x0300U)
#define GICR_SGI_BASE_ICACTIVER0  (0x0380U)
#define GICR_SGI_BASE_IPRIORITYR  (0x0400U)
#define GICR_SGI_BASE_ICFGR0      (0x0C00U)
#define GICR_SGI_BASE_ICFGR1      (0x0C04U)
#define GICR_SGI_BASE_IGRPMODR0   (0x0D00U)
#define GICR_SGI_BASE_NSACR       (0x0E00U)

/* GICD_CTLR */
#define GICD_CTLR_ENABLE_G0   (0x00000001U)
#define GICD_CTLR_ENABLE_G1NS (0x00000002U)
#define GICD_CTLR_ENABLE_G1S  (0x00000004U)
#define GICD_CTLR_ARE_S       (0x00000010U)
#define GICD_CTLR_ARE_NS      (0x00000020U)
#define GICD_CTLR_DS          (0x00000040U)
#define GICD_CTLR_E1NWF       (0x00000080U)
#define GICD_CTLR_RWP         (0x80000000U)  /* Register Write Pending, Read only */

/* GICD_CTLR Bits */
#define GICD_CTLR_DS_BIT            6
#define GICD_CTLR_ENABLE_G1S_BIT    2

/* GICD_CTLR Masks */
#define GICD_CTLR_RWP_MASK    GICD_CTLR_RWP  
#define GICD_CTLR_DS_MASK     GICD_CTLR_DS 

/* GICD_TYPER Masks */
#define GICD_TYPER_ITLINESNUM_MASK (0x0000001FU)

/* GICR_CTLR */
#define GICR_CTLR_RWP         (0x00000008U)

/* GICR_CTLR Masks */
#define GICR_CTLR_RWP_MASK    GICR_CTLR_RWP 

/* GICR_WAKER */
#define GICR_WAKER_CA   (0x00000004U)
#define GICR_WAKER_PS   (0x00000002U)

/* GICR_WAKER Bits */
#define GICR_WAKER_PS_BIT   1

#define GIC_SPI_INT_BASE		32
#define GIC_NUM_INTR_PER_REG    32
#define GIC_NUM_CFG_PER_REG		16
#define GIC_NUM_PRI_PER_REG		4

/*
 * '0xa0'is used to initialize each interrupt default priority.
 * This is an arbitrary value in current context.
 * Any value '0x80' to '0xff' will work for both NS and S state.
 * The values of individual interrupt and default has to be chosen
 * carefully if PMR and BPR based nesting and preemption has to be done.
 */
#define GIC_INT_DEF_PRI_X4		0xa0a0a0a0

void dt_gicv3_init(const void *fdt, int offset);

#endif 

