/*
 * Copyright (c) 2012 mike@xenonym.com
 *
 * $Id:$
 *
 * This the platform/arch specific methods.  
 *
 */

/*extern "C" void getCPU( CPU* cpu);*/
.global	getCPU

/*
// struct CPU_S
// {
//	 int cpsr;
//	 int r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;
// };
*/
getCPU:
	str r0,  [r0, #4]
	str r1,  [r0, #8]
	str r2,  [r0,#12]
	str r3,  [r0,#16]
	str r4,  [r0,#20]
	str r5,  [r0,#24]
	str r6,  [r0,#28]
	str r7,  [r0,#32]
	str r9,  [r0,#36]
	str r10, [r0,#40]
	str r11, [r0,#44]
	str r12, [r0,#48]
	str r13, [r0,#52]
	str r14, [r0,#56]
	str r15, [r0,#60]

	MRS r1, cpsr
	str r1, [r0]

	bx lr

/* extern "C" void setSCR(int scr); */
.global	setSCR
setSCR:
	mcr p15, 0, r0, c1, c1, 0    /*; Write Secure Configuration Register data */
	bx lr

/* extern "C" int CP15_MainID(); */
.global	CP15_MainID
CP15_MainID:
	mrc p15, 0, r0, c0, c0, 0    /*; Read CP15 Main ID */
	bx lr

/* extern "C" int CP15_CacheType(); */
.global	CP15_CacheType
CP15_CacheType:
	mrc p15, 0, r0, c0, c0, 1    /*; Read Cache type */
	bx lr

/* extern "C" int CP15_TcmStatus(); */
.global	CP15_TcmStatus
CP15_TcmStatus:
	mrc p15, 0, r0, c0, c0, 2    /*; Read TCM Status */
	bx lr

/* extern "C" int CP15_TlbType(); */
.global	CP15_TlbType
CP15_TlbType:
	mrc p15, 0, r0, c0, c0, 3    /*; Read TLB Type */
	bx lr

/* extern "C" int CP15_CPUID_PFR0(); */
.global	CP15_CPUID_PFR0
CP15_CPUID_PFR0:
	mrc p15, 0, r0, c0, c1, 0    /*; Read CPUID_PFR0 */
	bx lr

/* extern "C" int CP15_CPUID_PFR1(); */
.global	CP15_CPUID_PFR1
CP15_CPUID_PFR1:
	mrc p15, 0, r0, c0, c1, 1    /*; Read CPUID_PFR1 */
	bx lr

/* extern "C" int CP15_CPUID_DFR0(); */
.global	CP15_CPUID_DFR0
CP15_CPUID_DFR0:
	mrc p15, 0, r0, c0, c1, 2    /*; Read CPUID_DFR0 */
	bx lr

/* extern "C" int CP15_CPUID_AFR0(); */
.global	CP15_CPUID_AFR0
CP15_CPUID_AFR0:
	mrc p15, 0, r0, c0, c1, 3    /*; Read CPUID_AFR0 */
	bx lr

/* extern "C" int CP15_CPUID_MMFR0(); */
.global	CP15_CPUID_MMFR0
CP15_CPUID_MMFR0:
	mrc p15, 0, r0, c0, c1, 4    /*; Read CPUID_MMFR0 */
	bx lr

/* extern "C" int CP15_CPUID_MMFR1(); */
.global	CP15_CPUID_MMFR1
CP15_CPUID_MMFR1:
	mrc p15, 0, r0, c0, c1, 5    /*; Read CPUID_MMFR1 */
	bx lr

/* extern "C" int CP15_CPUID_MMFR2(); */
.global	CP15_CPUID_MMFR2
CP15_CPUID_MMFR2:
	mrc p15, 0, r0, c0, c1, 6    /*; Read CPUID_MMFR2 */
	bx lr

/* extern "C" int CP15_CPUID_MMFR3(); */
.global	CP15_CPUID_MMFR3
CP15_CPUID_MMFR3:
	mrc p15, 0, r0, c0, c1, 7    /*; Read CPUID_MMFR3 */
	bx lr

/* extern "C" int CP15_CPUID_ISAR0(); */
.global	CP15_CPUID_ISAR0
CP15_CPUID_ISAR0:
	mrc p15, 0, r0, c0, c2, 0    /*; Read CPUID_ISAR0 */
	bx lr

/* extern "C" int CP15_CPUID_ISAR1(); */
.global	CP15_CPUID_ISAR1
CP15_CPUID_ISAR1:
	mrc p15, 0, r0, c0, c2, 1    /*; Read CPUID_ISAR1 */
	bx lr

/* extern "C" int CP15_CPUID_ISAR2(); */
.global	CP15_CPUID_ISAR2
CP15_CPUID_ISAR2:
	mrc p15, 0, r0, c0, c2, 2    /*; Read CPUID_ISAR2 */
	bx lr

/* extern "C" int CP15_CPUID_ISAR3(); */
.global	CP15_CPUID_ISAR3
CP15_CPUID_ISAR3:
	mrc p15, 0, r0, c0, c2, 3    /*; Read CPUID_ISAR3 */
	bx lr

/* extern "C" int CP15_CPUID_ISAR4(); */
.global	CP15_CPUID_ISAR4
CP15_CPUID_ISAR4:
	mrc p15, 0, r0, c0, c2, 4    /*; Read CPUID_ISAR4 */
	bx lr

/* extern "C" int CP15_CPUID_ISAR5(); */
.global	CP15_CPUID_ISAR5
CP15_CPUID_ISAR5:
	mrc p15, 0, r0, c0, c2, 5    /*; Read CPUID_ISAR5 */
	bx lr

/* extern "C" int CP15_CR(); */
.global	CP15_CR
CP15_CR:
	mrc p15, 0, r0, c1, c0, 0    /*; Read Configuration Register */
	bx lr

/* extern "C" int CP15_ACR(); */
.global	CP15_ACR
CP15_ACR:
	mrc p15, 0, r0, c1, c0, 1    /*; Read ACR */
	bx lr

/* extern "C" int CP15_CACR(); */
.global	CP15_CACR
CP15_CACR:
	mrc p15, 0, r0, c1, c0, 2    /*; Read CACR */
	bx lr

/* extern "C" int CP15_SCR(); */
.global	CP15_SCR
CP15_SCR:
	mrc p15, 0, r0, c1, c1, 0    /*; Read Secure Configuration Register data */
	bx lr

/* extern "C" int CP15_SDER(); */
.global	CP15_SDER
CP15_SDER:
	mrc p15, 0, r0, c1, c1, 1    /*; Read Secure Debug Enable Register */
	bx lr

/* extern "C" int CP15_NSACR(); */
.global	CP15_NSACR
CP15_NSACR:
	mrc p15, 0, r0, c1, c1, 2    /*; Read NSACR */
	bx lr

/* extern "C" int CP15_TTBR0(); */
.global	CP15_TTBR0
CP15_TTBR0:
	mrc p15, 0, r0, c2, c0, 0    /*; Read TTBR0 */
	bx lr

/* extern "C" int CP15_TTBR1(); */
.global	CP15_TTBR1
CP15_TTBR1:
	mrc p15, 0, r0, c2, c0, 1    /*; Read TTBR1 */
	bx lr

/* extern "C" int CP15_TTBCR(); */
.global	CP15_TTBCR
CP15_TTBCR:
	mrc p15, 0, r0, c2, c0, 2    /*; Read TTBCR */
	bx lr

/* extern "C" int CP15_DACR(); */
.global	CP15_DACR
CP15_DACR:
	mrc p15, 0, r0, c3, c0, 0    /*; Read DACR */
	bx lr

/* extern "C" int CP15_DFSR(); */
.global	CP15_DFSR
CP15_DFSR:
	mrc p15, 0, r0, c5, c0, 0    /*; Read DFSR */
	bx lr

/* extern "C" int CP15_IFSR(); */
.global	CP15_IFSR
CP15_IFSR:
	mrc p15, 0, r0, c5, c0, 1    /*; Read IFSR */
	bx lr

/* extern "C" int CP15_FAR(); */
.global	CP15_FAR
CP15_FAR:
	mrc p15, 0, r0, c6, c0, 0    /*; Read FAR */
	bx lr

/* extern "C" int CP15_IFAR(); */
.global	CP15_IFAR
CP15_IFAR:
	mrc p15, 0, r0, c6, c0, 2    /*; Read IFAR */
	bx lr

