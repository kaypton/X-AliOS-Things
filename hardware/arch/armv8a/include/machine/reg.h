#ifndef __REG_H__
#define __REG_H__

#define	CNTHCTL_EL1PCEN		(1 << 1) /* Allow EL0/1 physical timer access */
#define	CNTHCTL_EL1PCTEN	(1 << 0) /*Allow EL0/1 physical counter access*/


#define PSR_M_EL1h 0x00000005

#define PSR_F 0x00000040
#define PSR_I 0x00000080
#define PSR_A 0x00000100
#define PSR_D 0x00000200

#define PSR_DAIF (PSR_D | PSR_I | PSR_A | PSR_F)

#define ICC_SRE_ELx_SRE (0x00000001U)
#define ICC_SRE_ELx_DFB (0x00000002U)
#define ICC_SRE_ELx_DIB (0x00000004U)
#define ICC_SRE_ELx_EN  (0x00000008U)

#define MPIDR_AFF0_MASK  (0x000000FFU)
#define MPIDR_AFF1_MASK  (0x0000FF00U)
#define MPIDR_AFF2_MASK  (0x00FF0000U)
#define MPIDR_MT_MASK    (0x01000000U)
#define MPIDR_U_MASK     (0x40000000U)

/* System register interface to GICv3 */
#define ICC_IGRPEN1_EL1		S3_0_C12_C12_7
#define ICC_SGI1R		S3_0_C12_C11_5
#define ICC_SRE_EL1		S3_0_C12_C12_5
#define ICC_SRE_EL2		S3_4_C12_C9_5
#define ICC_SRE_EL3		S3_6_C12_C12_5
#define ICC_CTLR_EL1		S3_0_C12_C12_4
#define ICC_CTLR_EL3		S3_6_C12_C12_4
#define ICC_PMR_EL1		S3_0_C4_C6_0
#define ICC_RPR_EL1		S3_0_C12_C11_3
#define ICC_IGRPEN1_EL3		S3_6_C12_C12_7
#define ICC_IGRPEN0_EL1		S3_0_C12_C12_6
#define ICC_HPPIR0_EL1		S3_0_C12_C8_2
#define ICC_HPPIR1_EL1		S3_0_C12_C12_2
#define ICC_IAR0_EL1		S3_0_C12_C8_0
#define ICC_IAR1_EL1		S3_0_C12_C12_0
#define ICC_EOIR0_EL1		S3_0_C12_C8_1
#define ICC_EOIR1_EL1		S3_0_C12_C12_1
#define ICC_SGI0R_EL1		S3_0_C12_C11_7

#endif 