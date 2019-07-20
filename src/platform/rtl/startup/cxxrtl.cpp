/*
 * Copyright (c) 2013 github@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *
 */
#include "cxxrtl.h"
#include "../memory/cxxrtl_malloc.h"

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

void * operator new(unsigned int len) {
	return platform::rtl::memory::allocate_memory(len);
}

void operator delete(void* ptr)
{
	platform::rtl::memory::free_memory(ptr);
}
