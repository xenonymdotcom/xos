/*
 * Copyright (c) 2013 mike@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *
 */
#include "cxxrtl_malloc.h"
#include "../startup/cxxrtl.h"

namespace platform {
namespace rtl {
namespace memory {

namespace MallocStatus
{
	enum MallocStatus
	{
	Free, InUse;
	}
}

struct MallocBlock
{
	MallocBlock * next;
	MallocStatus::MallocStatus status;
};

struct AllocatedMallocBlock : public MallocBlock
{
	int data[0];
}

struct FreeMallocBlock : public MallocBlock
{
	FreeMallocBlock * nextFree;
}


 

} } }

