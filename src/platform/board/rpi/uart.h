/*
 * Copyright (c) 2019 github@xenonym.com
 *
 * $Id:$
 *
 * This the interface to the pl011 UART.  
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
            void init_UART();
            
			class UART
			{
			public:
				virtual ~UART();
				virtual bool has_read_data();
				virtual uint8_t read();
				virtual bool can_send_write_data();
				virtual void write(uint8_t data);
				static UART& getUART(int channel);
				void write(char const * str){
					while(*str) write(static_cast<uint8_t>(*str++));
				}
			};			
		}
	}
}