/*
 * Copyright (c) 2013 github@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *  - the C++ startup code that will in turn call main
 *
 */
#include "cxxrtl.h"

// main is a C++ NOT C extern 
extern void main(void);

// then some exit code.
extern void private_fb_finish(void);

using namespace platform::rtl::startup;

// our startup point is however a extern C as it is called from the asm code.
extern "C" void __main(void)
{
	// loop forever as we are not expecting main to exit.
	while( true )
	{
		// zero the bss
		int * ptr = _bss_start;
		while( ptr < _bss_end )
		{
			*ptr++ = 0;
		}
		
		// call the static initialisers
	    constructorFunc *fn_init = _init_array_start;
	    while(fn_init < _init_array_end) 
	    {
	   		(*fn_init++)();
	    }
	
		main();
		
		// for now call the framebuffer exit code.
		private_fb_finish();		
	}
	return;	
}

