/*
 * Copyright (c) 2012 mike@xenonym.com
 *
 * $Id:$
 *
 * This the platform/arch specific methods.  
 *
 */
#pragma once

struct CPU_S
{
	int cpsr;
	int r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;
};

typedef struct CPU_S CPU;

extern "C" void getCPU( CPU* cpu);

extern "C" void setSCR(int scr);

extern "C" int CP15_MainID();
extern "C" int CP15_CacheType();
extern "C" int CP15_TcmStatus();
extern "C" int CP15_TlbType();
extern "C" int CP15_CPUID_PFR0();
extern "C" int CP15_CPUID_PFR1();
extern "C" int CP15_CPUID_DFR0();
extern "C" int CP15_CPUID_AFR0();
extern "C" int CP15_CPUID_MMFR0();
extern "C" int CP15_CPUID_MMFR1();
extern "C" int CP15_CPUID_MMFR2();
extern "C" int CP15_CPUID_MMFR3();
extern "C" int CP15_CPUID_ISAR0();
extern "C" int CP15_CPUID_ISAR1();
extern "C" int CP15_CPUID_ISAR2();
extern "C" int CP15_CPUID_ISAR3();
extern "C" int CP15_CPUID_ISAR4();
extern "C" int CP15_CPUID_ISAR5();
extern "C" int CP15_CR();
extern "C" int CP15_ACR();
extern "C" int CP15_CACR();
extern "C" int CP15_SCR();
extern "C" int CP15_SDER();
extern "C" int CP15_NSACR();
extern "C" int CP15_TTBR0();
extern "C" int CP15_TTBR1();
extern "C" int CP15_TTBCR();
extern "C" int CP15_DACR();
extern "C" int CP15_DFSR();
extern "C" int CP15_IFSR();
extern "C" int CP15_FAR();
extern "C" int CP15_IFAR();

