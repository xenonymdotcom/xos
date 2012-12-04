/*
 * Copyright (c) 2012 mike@xenonym.com
 *
 * $Id:$
 *
 * This staing point for the body of my OS.  
 *
 */

#include <platform/board/rpi/framebuffer.h>
#include <platform/board/rpi/textutils.h>
#include <platform/arch/arm/cpu.h>

using namespace platform::board::rpi;

extern "C" void __aeabi_unwind_cpp_pr0(void)
{
}

void dump_reg( int r0, int r1, int r2, int r3 )
{
	CPU cpu;
	getCPU( &cpu );

	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );
 	console_write(    "R0:0x");  console_write( tohex(cpu.r0,4) );
 	console_write(   " R1:0x");  console_write( tohex(cpu.r1,4) );
 	console_write(   " R2:0x");  console_write( tohex(cpu.r2,4) );
 	console_write(   " R3:0x");  console_write( tohex(cpu.r3,4) );
 	console_write(  "\nR4:0x");  console_write( tohex(cpu.r4,4) );
 	console_write(   " R5:0x");  console_write( tohex(cpu.r5,4) );
 	console_write(   " R6:0x");  console_write( tohex(cpu.r6,4) );
 	console_write(   " R7:0x");  console_write( tohex(cpu.r7,4) );
 	console_write(  "\nR8:0x");  console_write( tohex(cpu.r8,4) );
 	console_write(   " R9:0x");  console_write( tohex(cpu.r9,4) );
 	console_write(  " R10:0x"); console_write( tohex(cpu.r10,4) );
 	console_write(  " R11:0x"); console_write( tohex(cpu.r11,4) );
 	console_write( "\nR12:0x"); console_write( tohex(cpu.r12,4) );
 	console_write(  " R13:0x"); console_write( tohex(cpu.r13,4) );
 	console_write(  " R14:0x"); console_write( tohex(cpu.r14,4) );
 	console_write(  " R15:0x"); console_write( tohex(cpu.r15,4) );
	console_write( COLOUR_POP "\n" );

	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );
	if (cpu.cpsr & (1<<31)) { console_write( COLOUR_PUSH FG_RED "N" COLOUR_POP); } else {console_write("n");}
	if (cpu.cpsr & (1<<30)) { console_write( COLOUR_PUSH FG_RED "Z" COLOUR_POP); } else {console_write("z");}
	if (cpu.cpsr & (1<<29)) { console_write( COLOUR_PUSH FG_RED "C" COLOUR_POP); } else {console_write("c");}
	if (cpu.cpsr & (1<<28)) { console_write( COLOUR_PUSH FG_RED "V" COLOUR_POP); } else {console_write("v");}
	if (cpu.cpsr & (1<<27)) { console_write( COLOUR_PUSH FG_RED "Q" COLOUR_POP); } else {console_write("q");}

	if (cpu.cpsr & (1<<24)) { console_write( COLOUR_PUSH FG_RED "J" COLOUR_POP); } else {console_write("j");}

	if (cpu.cpsr & (1<<9)) { console_write( COLOUR_PUSH FG_RED "E" COLOUR_POP); } else {console_write("e");}
	if (cpu.cpsr & (1<<8)) { console_write( COLOUR_PUSH FG_RED "A" COLOUR_POP); } else {console_write("a");}
	if (cpu.cpsr & (1<<7)) { console_write( COLOUR_PUSH FG_RED "I" COLOUR_POP); } else {console_write("i");}
	if (cpu.cpsr & (1<<6)) { console_write( COLOUR_PUSH FG_RED "F" COLOUR_POP); } else {console_write("f");}
	if (cpu.cpsr & (1<<5)) { console_write( COLOUR_PUSH FG_RED "T" COLOUR_POP); } else {console_write("t");}

	console_write( COLOUR_POP "\n" );
	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );

	console_write(tohex(cpu.cpsr&0x1F,1));
	switch(cpu.cpsr&0x1F)
	{
	case 0x10: console_write("  - USR" ); break;
	case 0x11: console_write("  - FIQ" ); break;
	case 0x12: console_write("  - IRQ" ); break;
	case 0x13: console_write("  - SVR" ); break;
	case 0x17: console_write("  - ABT" ); break;
	case 0x1B: console_write("  - UDF" ); break;
	case 0x1F: console_write("  - SYS" ); break;
	case 0x16: console_write("  - MON" ); break;
	default:   console_write("  - ..." ); break;
	}

	console_write( COLOUR_POP "\n" );
}

extern "C" void main(void)
{
	fb_init();

	console_write( COLOUR_PUSH BG_BLUE BG_HALF FG_CYAN "more stuff" COLOUR_POP "\n" );

	dump_reg( 0x12345678, 0xc0def00d, 0xdeadbeaf, 0x80000001 );

	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );
	console_write("SCR:");
	console_write(tohex(CP15_SCR(),4));
	console_write( COLOUR_POP "\n" );

	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );

	console_write("ID:");
	console_write(tohex(CP15_MainID(),4));
	console_write( "\nCacheType:" );
	console_write(tohex(CP15_CacheType(),4));
	console_write( "\nTcmStatus:" );
	console_write(tohex(CP15_TcmStatus(),4));
	console_write( "\nTlbType:" );
	console_write(tohex(CP15_TlbType(),4));

	console_write( "\nCPUID_PFR0:" );
	console_write(tohex(CP15_CPUID_PFR0(),4));
	console_write( " CPUID_PFR1:" );
	console_write(tohex(CP15_CPUID_PFR1(),4));

	console_write( "\nCCP15_CPUID_DFR0:" );
	console_write(tohex(CP15_CPUID_DFR0(),4));
	console_write( " CCP15_CPUID_AFR0:" );
	console_write(tohex(CP15_CPUID_AFR0(),4));

	console_write( "\nCPUID_MMFR0:" );
	console_write(tohex(CP15_CPUID_MMFR0(),4));
	console_write( " MMFR1:" );
	console_write(tohex(CP15_CPUID_MMFR1(),4));
	console_write( " MMFR2:" );
	console_write(tohex(CP15_CPUID_MMFR2(),4));
	console_write( " MMFR3:" );
	console_write(tohex(CP15_CPUID_MMFR3(),4));

	console_write( "\nCPUID_ISAR0:" );
	console_write(tohex(CP15_CPUID_ISAR0(),4));
	console_write( " ISAR1:" );
	console_write(tohex(CP15_CPUID_ISAR1(),4));
	console_write( " ISAR2:" );
	console_write(tohex(CP15_CPUID_ISAR2(),4));
	console_write( " ISAR3:" );
	console_write(tohex(CP15_CPUID_ISAR3(),4));
	console_write( " ISAR4:" );
	console_write(tohex(CP15_CPUID_ISAR4(),4));
	console_write( " ISAR5:" );
	console_write(tohex(CP15_CPUID_ISAR5(),4));

	console_write( COLOUR_POP "\n" );
}

