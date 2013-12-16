#ifndef MSR_SUPPLEMENTAL_H
#define MSR_SUPPLEMENTAL_H

/* TLCC2 machines are based on Sandy Bridge Server processors, family 06 model 2D.*/

#ifdef _USE_ARCH_062D

// These registers need to be restored to sane values on program exit.  
// SLURM should call VIRTUAL_MSR_SAVE_CURRENT_VALUES on program start and
// VIRTUAL_MSR_RESTORE_OLD_VALUES on program exit.

#define NO_WRITE_ON_EXIT		(-1)
#define ZERO_OUT_MSR_ON_EXIT		(0)
#define SMSR_CLOCK_MODULATION_IDX 	(1)
#define SMSR_MISC_ENABLE_IDX		(2)
#define SMSR_ENERGY_PERF_BIAS_IDX	(3)
#define SMSR_PKG_POWER_LIMIT_IDX	(4)
#define SMSR_PP0_POWER_LIMIT_IDX	(5)
#define SMSR_DRAM_POWER_LIMIT_IDX	(6)

// Granularity of MSRs
#define SMSR_VIRTUAL			(0)
#define SMSR_THREAD			(1)
#define	SMSR_CORE			(2)
#define SMSR_PACKAGE			(3)
#define SMSR_SPECIAL			(4) //MISC_ENABLE has multiple granularities.

/* The Whitelist.
 *
 * 1) Things that access or modify interrupts are considered exploitable.
 * 	Don't allow access to temperature thresholds, interrupt vectors, etc.
 *
 * 2) Debugging features are problematic as they might allow the user access 
 * 	to kernel memory.
 *
 * 3) Writing records to DRAM (a la PEBS) needs a dedicated interface.
 * 	Don't put it here.
 *
 * 4) Anything that affects performance needs to be reset on program exit.
 *
 * 5) Performance counters should be zeroed out and disabled.
 *
 * 6) If we don't see an immediate need for access to an MSR, leave it out.
 */

//						perm	read	write-on-
//						0=ro	on	exit
// Name					Address 1=rw	start 	idx			granularity
//-----------------------------------------------------------------------------------------------------

// "virtual" msrs.
#define VIRT_MSR_SAVE_CURRENT_VALUES	0xFF00,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_VIRTUAL
#define VIRT_MSR_RESTORE_PREV_VALUES  	0xFF01,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_VIRTUAL
#define VIRT_MSR_RESTORE_SANE_VALUES	0xFF02,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_VIRTUAL

// MSRs taken from section 35.8 table 35-12
#define SMSR_TIME_STAMP_COUNTER		0x010,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_PLATFORM_ID		0x017,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_PMC0			0x0C1,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PMC1			0x0C2,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PMC2			0x0C3,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PMC3			0x0C4,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PMC4			0x0C5,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_CORE
#define SMSR_PMC5			0x0C6,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_CORE
#define SMSR_PMC6			0x0C7,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_CORE
#define SMSR_PMC7			0x0C8,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_CORE
#define SMSR_MPERF			0x0E7,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_APERF			0x0E8,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_PERFEVTSEL0		0x186,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PERFEVTSEL1		0x187,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_THREAD
#define SMSR_PERFEVTSEL2		0x188,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_THREAD
#define SMSR_PERFEVTSEL3		0x189,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_THREAD
#define SMSR_PERFEVTSEL4		0x18A,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_CORE
#define SMSR_PERFEVTSEL5		0x18B,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_CORE
#define SMSR_PERFEVTSEL6		0x18C,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_CORE
#define SMSR_PERFEVTSEL7		0x18D,	1,	0,	ZERO_OUT_MSR_ON_EXIT,   SMSR_CORE
#define SMSR_PERF_STATUS		0x198,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_PERF_CTL			0x199,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_CLOCK_MODULATION		0x19A,	1,	1,	SMSR_CLOCK_MODULATION_IDX,	SMSR_THREAD
#define SMSR_THERM_STATUS		0x19C,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_CORE
#define SMSR_MISC_ENABLE		0x1A0,	1,	1,	SMSR_MISC_ENABLE_IDX,	SMSR_SPECIAL
#define SMSR_OFFCORE_RSP_0		0x1A6,	1,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_OFFCORE_RSP_1		0x1A7,	1,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_ENERGY_PERF_BIAS		0x1B0,	1,	1,	SMSR_ENERGY_PERF_BIAS_IDX,	SMSR_PACKAGE
#define SMSR_PACKAGE_THERM_STATUS	0x1B1,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_FIXED_CTR0			0x309,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD	
#define SMSR_FIXED_CTR1			0x30A,	1,	0,	ZERO_OUT_MSR_ON_EXIT, 	SMSR_THREAD
#define SMSR_FIXED_CTR2			0x30A,	1,	0,	ZERO_OUT_MSR_ON_EXIT, 	SMSR_THREAD
#define SMSR_PERF_CAPABILITIES		0x345,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_FIXED_CTR_CTRL		0x38D,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PERF_GLOBAL_STATUS		0x38E,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_THREAD
#define SMSR_PERF_GLOBAL_CTRL		0x38F,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PERF_GLOBAL_OVF_CTRL	0x390,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PEBS_ENABLE		0x3F1,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_PEBS_LD_LAT		0x3F6,	1,	0,	ZERO_OUT_MSR_ON_EXIT,	SMSR_THREAD
#define SMSR_RAPL_POWER_UNIT		0x606,	0, 	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_PKG_POWER_LIMIT		0x610,	1,	1,	SMSR_PKG_POWER_LIMIT_IDX, SMSR_PACKAGE
#define SMSR_PKG_ENERGY_STATUS		0x611,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_PKG_POWER_INFO		0x612,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_PP0_POWER_LIMIT		0x638,	1,	1,	SMSR_PP0_POWER_LIMIT_IDX,SMSR_PACKAGE
#define SMSR_PP0_ENERGY_STATUS		0x639,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE

//MSRs taken from section 35.8 table 35-14
#define SMSR_MSR_PKG_PERF_STATUS	0x613,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_DRAM_POWER_LIMIT		0x618,	1,	1,	SMSR_DRAM_POWER_LIMIT_IDX, SMSR_PACKAGE
#define SMSR_DRAM_ENERGY_STATUS		0x619,	0,	0,	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_DRAM_PERF_STATUS		0x61B,	0,	0, 	NO_WRITE_ON_EXIT,	SMSR_PACKAGE
#define SMSR_DRAM_POWER_INFO		0x61C,	0,	0, 	NO_WRITE_ON_EXIT,	SMSR_PACKAGE


/*Patki*/
#define MSR_LAST_ENTRY ~0
#define FAKE_LAST_MSR MSR_LAST_ENTRY, 0,0,0,0


#endif //_USE_ARCH_062D

#endif /* MSR_SUPPLEMENTAL_H */