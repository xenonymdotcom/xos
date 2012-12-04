/*
 * Copyright (c) 2012 mike@xenonym.com
 *
 * $Id:$
 *
 * This the interface to the broadcom GPU mailbox.  
 *
 */
#pragma once
namespace platform
{
	namespace board
	{
		namespace rpi
		{
			unsigned int mailbox_read(unsigned int channel);
			void mailbox_write(unsigned int channel, unsigned int * data);
		}
	}
}

