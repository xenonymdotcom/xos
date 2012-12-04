/*
 * Copyright (c) 2012 mike@xenonym.com
 *
 * $Id:$
 *
 * This the interface to the broadcom GPU mailbox.  
 *
 */
#include <platform/arch/arm/platform.h>
#include "mailbox.h"


// Mailbox memory addresses
namespace
{
	volatile unsigned int * const MAILBOX0READ = (unsigned int *) 0x2000b880;
	volatile unsigned int * const MAILBOX0STATUS = (unsigned int *) 0x2000b898;
	volatile unsigned int * const MAILBOX0WRITE = (unsigned int *) 0x2000b8a0;
	// Bit 31 set in status register if the write mailbox is full
	unsigned int const MAILBOX_FULL = 0x80000000;

	// Bit 30 set in status register if the read mailbox is empty
	unsigned int const MAILBOX_EMPTY = 0x40000000;
}

namespace platform { 
namespace board {
namespace rpi {

unsigned int mailbox_read(unsigned int channel)
{
	unsigned int count = 0;
	unsigned int data;

	// Loop until something is received from channel
	// If nothing recieved, it eventually give up and returns 0xffffffff
	do
	{
		while (*MAILBOX0STATUS & MAILBOX_EMPTY)
		{
			// Need to check if this is the right thing to do
			flushcache();
		}
		// Read the data, Data memory barriers as we've switched peripheral
		dmb();
		data = *MAILBOX0READ;
		dmb();

		if ((data & 15) == channel)
			return data;
	}
	while(++count < (1<<25));

	return ~0;
}

void mailbox_write(unsigned int channel, unsigned int * data)
{
	// Wait for mailbox to be not full
	while (*MAILBOX0STATUS & MAILBOX_FULL)
	{
		// Need to check if this is the right thing to do
		flushcache();
	}

	dmb();
	*MAILBOX0WRITE = (((unsigned int)data) | channel);
	dmb();
}

}
}
}
