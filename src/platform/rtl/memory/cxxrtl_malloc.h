/*
 * Copyright (c) 2013 mike@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *
 */
#pragma once;

namespace platform {
namespace rtl {
namespace memory {

// malloc
void * allocate_memory(int length, bool fill = false, int fillvalue=0);

//free
void free_memory(void* ptr);

}}}
