/*
 * Copyright (c) 2013 github@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *
 */
#pragma once

// these are all linker defines
namespace platform { 
namespace rtl {
namespace startup {

typedef void (*constructorFunc)(void);

// this first static constcutor function
extern "C" constructorFunc _init_array_start[];

// the next pointer after the last static constructor
extern "C" constructorFunc _init_array_end[];

// The data/memory values.

// the begining of the bcc (zero init) section
extern "C" int _bss_start[];
// the next int after the end of the bcc (zero init) section
extern "C" int _bss_end[];

// The first free word (the begining of the heap).
extern "C" int _heap_start[];

}
}
}

