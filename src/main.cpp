/*
 * Copyright (c) 2012 github@xenonym.com
 *
 * $Id:$
 *
 * This staing point for the body of my OS.  
 *
 */

#include <platform/board/rpi/framebuffer.h>
#include <platform/board/rpi/textutils.h>
#include <platform/board/rpi/uart.h>
#include <platform/arch/arm/cpu.h>
#include <platform/rtl/memory/cxxrtl_malloc.h>

using namespace platform::board::rpi;

/*

namespace __cxxabiv
{
	void __class_type_info() { return; } // (void*)0; }
	void __si_class_type_info();
	extern void * vtable;
	void * vtable;

}
extern "C" void * vtable;
void * vtable;
*/
double calcSomeStuff( int a, int b )
{
	float aa = a*.01f;
	double bb = b*0.27;
	return (aa+bb)/34.76;
}

char buffer[256];
int out_idx=0;
int in_idx=0;

bool get_from_buffer(char * ptr) {
	if (in_idx == out_idx) return false;
	*ptr = buffer[out_idx];
	out_idx = (out_idx + 1) & 0xFF;
	return true;
}

void write_to_buffer(char const * str) {
	while (*str) {
		int nxt_in = (in_idx + 1) & 0xFF;
		if (nxt_in == out_idx) return;
		buffer[in_idx] = *str++;
		in_idx = nxt_in;
	} 
}

void dump_reg( int r0, int r1, int r2, int r3 )
{
	CPU cpu;
	getCPU( &cpu );

	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );
 	console_write(   " R0:0x"); console_write( tohex(cpu.r0,4) );
 	console_write(  "  R1:0x"); console_write( tohex(cpu.r1,4) );
 	console_write(  "  R2:0x"); console_write( tohex(cpu.r2,4) );
 	console_write(  "  R3:0x"); console_write( tohex(cpu.r3,4) );
 	console_write( "\n R4:0x"); console_write( tohex(cpu.r4,4) );
 	console_write(  "  R5:0x"); console_write( tohex(cpu.r5,4) );
 	console_write(  "  R6:0x"); console_write( tohex(cpu.r6,4) );
 	console_write(  "  R7:0x"); console_write( tohex(cpu.r7,4) );
 	console_write( "\n R8:0x"); console_write( tohex(cpu.r8,4) );
 	console_write(  "  R9:0x"); console_write( tohex(cpu.r9,4) );
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
	double d = calcSomeStuff( cpu.r0, cpu.r1 );
	int res = (int)d;
//	int res = (int)0;
	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN "float->int check:0x");
	console_write(tohex(res,4));
	console_write( "Recv from UART -->\n:0000:" );

	UART& uart0 = UART::getUART(0);
	write_to_buffer("hello from XOS\n");
	int line_count=0;
	do {
		if (uart0.has_read_data()) {
			char c = (char)uart0.read();
			console_write(c);
			if (c == '\n') { 
				write_to_buffer("XOS recv line complete\n");
				console_write( ":" );
				console_write(todec(++line_count,4));
				console_write( ":" );
			}
		}
		if (uart0.can_send_write_data()) {
			char c;
			if (get_from_buffer(&c))
			{
				uart0.write(c);
			} 
		}
	} while (true);
	console_write( COLOUR_POP "\n" );
}

extern int doSum(int);

class Foo
{
public:
	Foo(int aa=2) : a(doSum(aa)),b(2),c(3),d(4) {}
int a,b,c,d;
} FooLocal;


Foo foo1(9);
Foo foo2(8);
Foo foo3(7);

int new_test() 
{
	Foo * fp = new Foo(99);
	int i = fp->b;
	delete fp;
	return i;
}


void main(void)
{
	//blat them
	foo1.a =0;foo1.b=foo1.c=foo1.d=~0;
	// capture the initial values of foo1 (before the static constructors are called)
	int a = foo1.a,b=foo1.b,c=foo1.c,d=foo1.d;

	fb_init();
	init_UART();

	console_write( COLOUR_PUSH BG_BLUE BG_HALF FG_CYAN "Foo1 initial (blatted)" );
	console_write(  " a:" );	console_write(tohex(a,4));
	console_write( ", b:" );	console_write(tohex(b,4));
	console_write( ", c:" );	console_write(tohex(c,4));
	console_write( ", d:" );	console_write(tohex(d,4));
	console_write( COLOUR_POP "\n");

	console_write( COLOUR_PUSH BG_BLUE BG_HALF FG_CYAN "Foo1 after");
	console_write(  " a:" );	console_write(tohex(foo1.a,4));
	console_write( ", b:" );	console_write(tohex(foo1.b,4));
	console_write( ", c:" );	console_write(tohex(foo1.c,4));
	console_write( ", d:" );	console_write(tohex(foo1.d,4));
	console_write( COLOUR_POP "\n");

	console_write( COLOUR_PUSH BG_BLUE BG_HALF FG_YELLOW "Foo1 after");
	console_write(  " ntr:" );	console_write(tohex(new_test(),4));
	console_write( COLOUR_POP "\n");
	

	    
	console_write( COLOUR_PUSH BG_BLUE BG_HALF FG_CYAN "FooLocal:" COLOUR_POP "\n" );
	console_write( COLOUR_PUSH BG_MAGENTA BG_HALF FG_GREEN );
	console_write(" a:");
	console_write(tohex(FooLocal.a,4));
	console_write(" b:");
	console_write(tohex(FooLocal.b,4));
	console_write(" c:");
	console_write(tohex(FooLocal.c,4));
	console_write(" d:");
	console_write(tohex(FooLocal.d,4));
	console_write( COLOUR_POP "\n" );

	console_write( COLOUR_PUSH BG_BLUE BG_HALF FG_CYAN "Registers:" COLOUR_POP "\n" );

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

