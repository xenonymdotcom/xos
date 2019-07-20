/*
 * Copyright (c) 2013 githubs@xenonym.com
 *
 * $Id:$
 *
 * This a minimul C++ runtime library
 *
 */
#include "cxxrtl_malloc.h"
#include "../startup/cxxrtl.h"
#include "../../arch/arm/arm_stdint.h"

namespace platform {
namespace rtl {
namespace memory {

namespace MallocStatus
{
	enum MallocStatus
	{
		End, Free, InUse
	};
}

struct MallocBlock
{
	MallocBlock * next;
	MallocStatus::MallocStatus status;
};

struct AllocatedMallocBlock : public MallocBlock
{
	int data[0];
};

struct FreeMallocBlock : public MallocBlock
{
	FreeMallocBlock * nextFree;
};

using namespace platform::rtl::startup;

template<int sizeInK> class HeapManager
{
private:
	int * m_start;
	int * m_end;
	FreeMallocBlock * m_freeList;
public:
	HeapManager() 
		: m_start(&_heap_start[0])
		, m_end(&_heap_start[(sizeInK/4)*1024])
	{
		m_freeList = (FreeMallocBlock *)m_start;
		MallocBlock * terminator = (MallocBlock *)(((uint8_t *)m_end)-sizeof(MallocBlock));
		terminator->next = 0;
		terminator->status = MallocStatus::End;
		
		m_freeList->next = terminator;
		m_freeList->status = MallocStatus::Free;
		m_freeList->nextFree = 0;
	}
	
	static int calcLength(MallocBlock * blk)
	{
		MallocBlock * nxt = blk->next;
		if (nxt)
		{
			return (((uint8_t *)nxt)-((uint8_t *)blk)) - sizeof(MallocBlock);
		}
		return 0;		
	}
	
	void * allocate(int requiredLength)
	{
		FreeMallocBlock ** blk = &m_freeList;
		while( calcLength(*blk) < requiredLength )
		{
			blk = reinterpret_cast<FreeMallocBlock**>(&((*blk)->next));
			// exit if we get to then end without finding a block that was long enough
			if ( !blk ) return 0;
		}
		// rethink! we need to walk the free list and then updated the chain.
		return &(reinterpret_cast<AllocatedMallocBlock*>(*blk)->data[0]);
	}
	
	void free(void * blk)
	{
		MallocBlock * actualBlk = (MallocBlock *)(((uint8_t *)blk)-sizeof(MallocBlock));
		actualBlk->next = m_freeList;
		actualBlk->status = MallocStatus::Free;
		m_freeList = reinterpret_cast<FreeMallocBlock*>(actualBlk);
	}
};

HeapManager<128> manager;

// malloc
void * allocate_memory(int length, bool fill, int fillvalue)
{
	void * ptr = manager.allocate(length);
	if (fill && ptr)
	{
		int8_t * mp = reinterpret_cast<int8_t *>(ptr);
		while(length--)
		{
			*mp++ = fillvalue;
		}
	}
	return ptr;
}

//free
void free_memory(void* ptr)
{
	// it is valid to call free with nullptr
	if (ptr) { manager.free(ptr); }
}

} } }



