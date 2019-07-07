/*
 * Copyright (c) 2012 github@xenonym.com
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
			char const *tohex(unsigned int value, unsigned int size);
			char const *todec(unsigned int value, int leading);
		}
	}
}

