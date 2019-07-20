/*
 * Copyright (c) 2019 github@xenonym.com
 *
 * $Id:$
 *
 * This the interface to the pl011 UART.  
 *
 */
#include "uart.h"
#include "mailbox.h"

/* Use some free memory in the area below the kernel/stack */
#define BUFFER_ADDRESS	0x1000

namespace 
{
  // gpio BASE is 0x3F200000 for pi 2 and above
  //                0x20200000 for pi 1
    unsigned int volatile * const GPFSEL0 = (volatile unsigned int*)0x20200000;
    unsigned int volatile * const GPFSEL1 = (volatile unsigned int*)0x20200004;
    unsigned int volatile * const GPFSEL2 = (volatile unsigned int*)0x20200008;
    unsigned int volatile * const GPFSEL3 = (volatile unsigned int*)0x2020000C;
    unsigned int volatile * const GPFSEL4 = (volatile unsigned int*)0x20200010;
    unsigned int volatile * const GPFSEL5 = (volatile unsigned int*)0x20200014;
    unsigned int volatile * const GPSET0  = (volatile unsigned int*)0x2020001C;
    unsigned int volatile * const GPSET1  = (volatile unsigned int*)0x20200020;
    unsigned int volatile * const GPCLR0  = (volatile unsigned int*)0x20200028;
    unsigned int volatile * const GPLEV0  = (volatile unsigned int*)0x20200034;
    unsigned int volatile * const GPLEV1  = (volatile unsigned int*)0x20200038;
    unsigned int volatile * const GPEDS0  = (volatile unsigned int*)0x20200040;
    unsigned int volatile * const GPEDS1  = (volatile unsigned int*)0x20200044;
    unsigned int volatile * const GPHEN0  = (volatile unsigned int*)0x20200064;
    unsigned int volatile * const GPHEN1  = (volatile unsigned int*)0x20200068;
    unsigned int volatile * const GPPUD   = (volatile unsigned int*)0x20200094;
    unsigned int volatile * const GPPUDCLK0 = (volatile unsigned int*)0x20200098;
    unsigned int volatile * const GPPUDCLK1 = (volatile unsigned int*)0x2020009C;

  // UART 0 BASE is 0x3F201000 for pi 2 and above
  //                0x20201000 for pi 1

    unsigned int volatile * const UART0_DR   = (unsigned int volatile *)0x20201000;
    unsigned int volatile * const UART0_SR   = (unsigned int volatile *)0x20201004;
    unsigned int volatile * const UART0_FR   = (unsigned int volatile *)0x20201018;
    unsigned int volatile * const UART0_IBRD = (unsigned int volatile *)0x20201024;
    unsigned int volatile * const UART0_FBRD = (unsigned int volatile *)0x20201028;
    unsigned int volatile * const UART0_LCRH = (unsigned int volatile *)0x2020102C;
    unsigned int volatile * const UART0_CR   = (unsigned int volatile *)0x20201030;
    unsigned int volatile * const UART0_IMSC = (unsigned int volatile *)0x20201038;
    unsigned int volatile * const UART0_ICR  = (unsigned int volatile *)0x20201044;
}

namespace platform {
namespace board {
namespace rpi {

void init_UART()
{
    // the init routine to setup the UARTS
	unsigned int * const mailbuffer = (unsigned int *)BUFFER_ADDRESS;
	
	MailBox& mailbox = MailBox::getMailBox(8);

    *UART0_CR = 0;         // turn off UART0

    // set up clock for consistent divisor values
    mailbuffer[0] = 9*4;
    mailbuffer[1] = 0; // MBOX_REQUEST;
    mailbuffer[2] = 0x38002; // MBOX_TAG_SETCLKRATE; // set clock rate
    mailbuffer[3] = 12;
    mailbuffer[4] = 8;
    mailbuffer[5] = 2;           // UART clock
    mailbuffer[6] = 4000000;     // 4Mhz
    mailbuffer[7] = 0;           // clear turbo
    mailbuffer[8] = 0; // MBOX_TAG_LAST;

	mailbox.write(mailbuffer);
	// unsigned int var = mailbox.read();
    mailbox.read();

    // map UART0 to GPIO pins
    unsigned int r=*GPFSEL1;
    r&=~((7<<12)|(7<<15)); // gpio14, gpio15
    r|=(4<<12)|(4<<15);    // alt0
    *GPFSEL1 = r;
    *GPPUD = 0;            // enable pins 14 and 15
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = (1<<14)|(1<<15);
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = 0;        // flush GPIO setup

    *UART0_ICR = 0x7FF;    // clear interrupts
    *UART0_IBRD = 2;       // 115200 baud
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0b1110000; // 8n1 + FIFO
    *UART0_CR = 0x301; // enable Tx, Rx, UART enable
}

class PL011UART : public UART {

    bool has_read_data() {
        return !(*UART0_FR & (1<<4)); // not recv fifo empty
    }

    uint8_t read()
    { 
        uint8_t r;
        // wait until something is in the buffer
        while(!has_read_data()){asm volatile("nop");}
        // read it and return
        r = (char)(*UART0_DR);
        return r;
    }

    bool can_send_write_data() {
        return !(*UART0_FR & (1<<5));  // not transmit fifo full
    }

    void write(uint8_t data)
    {
        // wait until we can send
        while(!can_send_write_data()){asm volatile("nop");}
        // write the character to the buffer
        *UART0_DR = data;
    }

} pl011;

UART nullUART;

// null implementation
UART::~UART() {}
bool UART::has_read_data() { return true; }
uint8_t UART::read() { return 0; }
bool UART::can_send_write_data() { return true; }
void UART::write(uint8_t data) {}

// for now only channel 0 is implented
// at some point channel 1 will be the other uart
UART& UART::getUART(int channel)
{
    return channel ? nullUART : pl011;
}
			
}}}
