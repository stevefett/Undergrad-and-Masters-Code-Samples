#include <spede/machine/io.h>
#include <spede/machine/rs232.h>
#include "kerneldata.h"
#include "TTYDriver.h"

/* This file gives a pseudo-code description of the kernel's first-level interrupt
 * handler for interrupt request (IRQ) 3 and 4.  The kernel must initialize the vectors
 * (interrupt descriptor table entries) for both IRQ3 and IRQ4 so that this routine is
 * called from the ISR 'switch' statement in the kernel which is executed after the state
 * of the running process has been saved.
 */
void IRQ34ISR() {
    int i;
	// We get here because an interrupt IRQ3 or IRQ4 has occurred, meaning
	// one (or more) serial port interrupt conditions exist.
	// We execute a loop checking ALL serial port conditions and service
	// them all before returning back to the kernel code which calls the
	// dispatcher.

	for (i=1; i<=MAX_TERMINALS; i++) {
        int status, pending;
		//read the Interrupt Identification Register for the ith serial port
		status = inportb(baseIO[i] + IIR);	//IIR_OFFSET = 2

		//mask out everything but the "interrupt pending" bit (bit 0)
		// (note that bit0 == 0  means pending, so we mask out all but that bit
		//  and then complement it; the result is a 1 if an interrupt is pending)
		pending = ~(status & 0x01) ;

		//loop until the current terminal port has no more interrupting conditions
		while (pending) {

			//use the two-bit ID field (bits 1 and 2) to determine what kind
			// of interrupt is pending:  01 = TBE,  10 = RDA.  Combined with the
			// 0 in bit zero, this means 010 (0x02) = TBE and 100 (0x04) = RDA
			switch (status) {

				//for TBE, call the output ISR for the current terminal
				case 0x02: PutChar(i);
							break;
				//for RDA, call the input ISR for the current terminal
				case 0x04: GetChar(i);
			}

			//read status again and check for more pending requests
			status = inportb(baseIO[i] + IIR);
			pending = ~(status & 0x01) ;

		} //end while this port has pending requests

		//at this point we've processed all pending interrupts for the current
		// terminal.  However, we might have input a character (case RDA above)
		// that got put into the Echo queue.  If we've already missed a TBE
		// interrupt, nothing will cause that character to get echoed -- so
		// we call the PutChar() function to have it check for something
		// needing output.
		if (ScreenInt[i]==TRUE) {
			PutChar(i) ;
		}

	}//end for each terminal

	//we've handled all interrupts for all terminals (serial ports);
	//  dismiss IRQs 3 & 4 in the Priority Interrupt Controller
	outportb (0x20, 0x63);	//0x2 = PIC control register; 0x63 and
	outportb (0x20, 0x64);	//  0x64 are commands to dismiss IRQ 3 & 4

}// end of IRQ34ISR;  return to kernel ISR switch (which will call the dispatcher)