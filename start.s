/* Set up stack and jump to C code */

.global	_start

_start:
	/* taken from the arm web site (http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0472i/CJAHIEDH.html) */
	MRC p15,0,r0,c1,c0,2    /* Read CP Access register */
	ORR r0,r0,#0x00f00000   /* Enable full access to NEON/VFP (Coprocessors 10 and 11) */
	MCR p15,0,r0,c1,c0,2    /* Write CP Access register */
	MOV r0,#0x40000000      /* Switch on the VFP and NEON hardware */
	fmxr fpexc,r0            /* Set EN bit in FPEXC */
		 
	/* kernel.img is loaded at 0x8000, so area under that can be the
	 * stack
	 */
	mov sp, #0x8000
	b __main
