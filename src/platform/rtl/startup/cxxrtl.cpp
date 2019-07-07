/*
 * Copyright (c) 2013 github@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *
 */
#include "cxxrtl.h"

extern "C" void __aeabi_unwind_cpp_pr0(void)
{
}

extern "C" void __aeabi_atexit(void)
{
}

extern "C" void __dso_handle(void)
{
}

extern "C" void __cxa_pure_virtual(void)
{
	while(1) { ; }
}

void operator delete(void*foo)
{
	return;	
}

