/*
 * Copyright (c) 2012 mike@xenonym.com
 *
 * $Id:$
 *
 * This the interface to the broadcom GPU mailbox.  
 *
 */
#pragma once

#include <stdint.h>

namespace platform
{
	namespace board
	{
		namespace rpi
		{
			class MailBox
			{
			public:
				virtual ~MailBox();
				virtual uint32_t read();
				virtual void write(uint32_t* data);
				static MailBox& getMailBox(int channel);
			};
			
			//unsigned int mailbox_read(unsigned int channel);
			//void mailbox_write(unsigned int channel, unsigned int * data);
		}
	}
}

