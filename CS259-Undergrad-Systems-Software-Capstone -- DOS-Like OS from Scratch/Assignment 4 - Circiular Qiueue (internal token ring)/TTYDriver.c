#include <spede/machine/io.h>
#include <spede/machine/rs232.h>
#include <spede/machine/pic.h>
#include "kerneldata.h"
#include "TTYDriver.h"
#include "OSAPI.h"
#include "circularqueue.h"

/* This file contains a pseudo-code description of the overall structure of a TTY
 *  driver -- both the top and bottom halves for both the input side and the output
 *  side.  It also describes the general setup of the "shared data structures":
 *  an input queue, output queue, and echo queue for each terminal.
 * Some of the constants used in the various modules in this file are defined in
 * various "spede" header files; see the Lab manual for details.
 */


/*  The following arrays track each terminal; that is, there is one element in each array for
 *  each terminal -- element [1] in each array is for Terminal #1; element [2] for
 *  terminal #2, etc.  We define one extra element because `TermNum'
 *  goes 1..N while C arrays are 0..N-1;  element 0 is not used.
 *
 *	ScreenInt[] - TRUE if TBE intr occurred on this terminal when no data was available to be sent.
 *	EchoMode[] - TRUE  if we should be echoing the user's input on this terminal
 *	CookedMode[] - TRUE if the driver should add RETURN after LINEFEED
 */
 
BOOL ScreenInt[ MAX_TERMINALS+1 ];
BOOL EchoMode[ MAX_TERMINALS+1 ];
BOOL CookedMode[ MAX_TERMINALS+1 ];

/* The following arrays implement the circular queues associated with each terminal;
 * again, element [1] in each array is for terminal #1, etc.
 * Note that the TYPE of the elements is "CircularQueue", which must be defined elsewhere.
 */
CircularQueue inqueue[ MAX_TERMINALS+1 ];
CircularQueue outqueue[ MAX_TERMINALS+1 ];
CircularQueue echoqueue[ MAX_TERMINALS+1 ];


/* These arrays define the IO base addresses and IRQ numbers associate with
 * each terminal.  As above, an unused element [0] is created so that
 * Terminal Numbers can be used as indexes into the array.
 */

int baseIO[] = { 0, 0x2F8, 0x3E8, 0x2E8, 0x2F0, 0x3E0 };
int baseIRQ[] = { 0,   3,     4,     3,     4,     3  };
int initDoneSemaphores[] = {0, TTY1_INIT_DONE_SEMAPHORE, TTY2_INIT_DONE_SEMAPHORE};
int outputSpaceAvailSemaphores[] = {0, TTY1_OUTPUT_SPACE_AVAILABLE_SEMAPHORE, TTY2_OUTPUT_SPACE_AVAILABLE_SEMAPHORE};
int inputDataAvailSemaphores[] = {0, TTY1_INPUT_DATA_AVAILABLE_SEMAPHORE, TTY2_INPUT_DATA_AVAILABLE_SEMAPHORE};


char GetCharFromEchoQueue(int TermNum){
    return RemoveFromQueue(&echoqueue[TermNum]);
}

char GetCharFromOutputQueue(int TermNum){
    return RemoveFromQueue(&outqueue[TermNum]);
}

char GetCharFromInputQueue(int TermNum){
    return RemoveFromQueue(&inqueue[TermNum]);
}

void InsertIntoEchoQueue(int TermNum, char ch){
    AddToQueue(&echoqueue[TermNum], ch);
}

void InsertIntoOutputQueue(int TermNum, char ch){
    AddToQueue(&outqueue[TermNum], ch);
}

void InsertIntoInputQueue(int TermNum, char ch){
    AddToQueue(&inqueue[TermNum], ch);
}

/*=====================================================================*/
/*   Code modules for the TTY Output Driver                            */
/*=====================================================================*/


/*---------------------------------------------------------------------*/
/* This is the initialization routine for a terminal. It is called by
 * the TTYWrite process driving the terminal. The routine initializes
 * the data structures and the hardware serial port state. When initialization
 * is complete the routine Signals the terminal's TTYInitDone Semaphore;
 * the TTYRead process for the terminal does a Wait on that semaphore and
 * doesn't try to read TTY input until the initialization is done (and the
 * semaphore has been Signalled).
 */
void InitTTY(int TermNum) {
    const unsigned	BAUD_RATE = 9600;
    const unsigned	divisor = 115200 / BAUD_RATE;
    int j;

    /* Initialize state flags. */
    ScreenInt[TermNum] = TRUE;
    CookedMode[TermNum] = TRUE;
    EchoMode[TermNum] = TRUE;

    /*  Setup the serial port for 7-E-1 at 9600 baud */
    outportb(baseIO[TermNum] + CFCR, CFCR_DLAB);
    outportb(baseIO[TermNum] + BAUDLO, LOBYTE(divisor));
    outportb(baseIO[TermNum] + BAUDHI, HIBYTE(divisor));

    outportb(baseIO[TermNum] + CFCR, CFCR_PEVEN | CFCR_PENAB | CFCR_7BITS);

    /*  Announce output slots available */
    for( j=0 ; j < CIRCULAR_QUEUE_CAPACITY ; ++j ) {
        SIGNAL(outputSpaceAvailSemaphores[TermNum]);
    }

    /*  Now we're ready, so raise DTR & RTS. Enable this IRQ, too. */
    outportb(baseIO[TermNum] + MCR, MCR_DTR | MCR_RTS /* | MCR_IENABLE */ );
    IRQEnable(baseIRQ[TermNum]);

    /* Signal other TTY direction that we're ready. */
    SIGNAL(initDoneSemaphores[TermNum]);

}   /* end InitTTY */


void Output(int TermNum, char ch){
    outportb(baseIO[TermNum], ch);
}


/*---------------------------------------------------------------------*/
/* TTY Driver Output Half Bottom-Half Interrupt Service Routine
 * This routine is the ISR for Transmit Buffer Empty (TBE) interrupts for
 * the specified TermNum. It is called from the kernel when a TBE interrupt occurs,
 * and called from the TTY Output Top Half if a TBE has already been missed.
 * It removes a char from the head of the specified terminal
 * output queue and outputs it to the terminal screen if
 * a char is available; otherwise sets a "missed interrupt" flag.
 * Assumes the Kernel first-level ISR will dismiss the interrupt.
 */
void PutChar (int TermNum) {
	//check for something to output
    bool echoQueueEmpty = IsQueueEmpty(&(echoqueue[TermNum]));
	if (IsQueueEmpty(&(outqueue[TermNum])) && echoQueueEmpty){
        //both the Output Queue and the Echo Queue for this TermNum are empty
		//there's nothing to output so set a flag indicating we missed a TBE int
		ScreenInt[TermNum] = TRUE ;

	} else {
        char OutChar;
        if (!echoQueueEmpty){
        //Echo Queue for this terminal is not empty
        //give priority to echoes

		OutChar = GetCharFromEchoQueue(TermNum);

        } else {
            OutChar = GetCharFromOutputQueue(TermNum);
            // Invoke Kernel routine to signal appropriate semaphore.
            //  Note that this is NOT a Trap (Int instruction)...
            
            SemaphorePost(outputSpaceAvailSemaphores[TermNum]);
            //KernelServices.Signal(Space Available semaphore for TermNum);
        }
		//output the char
		Output (TermNum,OutChar);	//use outportb()
	}
} //end of PutChar


/*---------------------------------------------------------------------*/
/* This routine is part of the Top Half of the Output Half of the TTY Driver.
 * It puts the specified character in the output queue for the specified terminal.
 * It insures critical-section protection for queue access by performing a Wait
 * on the "SpaceAvailable" semaphore for the terminal, then momentarily disables
 * interrupts while performing the actual queue insertion. Finally, it checks to
 * see whether the "Transmit Buffer Empty (TBE)" interrupt for this terminal has
 * already occurred; if so, it directly calls the "PutChar()" routine for the
 * terminal.  If not, it relys on the eventual next TBE interrupt to fetch the
 * character and output it.
 */
 void OutputChar(int TermNum, char theChar) {

     /*wait until there is space in the output queue*/
     WAIT(outputSpaceAvailSemaphores[TermNum]);

     /* CRITICAL SECTION: protect queue from simultaneous accesses */
     DI();

     /*put char in output queue*/
     InsertIntoOutputQueue(TermNum,theChar);

     /*check if screen interrupt for this char has already happened*/
     if(ScreenInt[TermNum]) {
		/*yes -- clear interrupt and force char out*/
		ScreenInt[TermNum] = FALSE ;
		PutChar(TermNum);
     }
     /* END CRITICAL SECTION: restore interrupt state */
     EI();

 } //end of OutputChar
 

/*---------------------------------------------------------------------*/
/* This routine changes the "mode" of the TTY driver.  It uses the input
 * parameter to turn echo on/off and to enable/disable "cooked-mode "
 * processing. Bit 0 of the input mode controls whether to echo,
 *	and bit 1 is cooked (1) or raw (0) mode.
 */
void SetTTYMode(int TermNum, int mode) {
    EchoMode[ TermNum ] = (mode & 1);
    CookedMode[ TermNum ] = ((mode >> 1) & 1);
}   /* end SetTTYMode() */


/*---------------------------------------------------------------------*/
/* This routine is part of the Top Half of the Output Half of the TTY Driver.
 * It displays characters from the specified buffer on the current user
 * terminal until NumCharsToWrite have been displayed, or a NUL is encountered,
 * whichever comes first.  If driver is in Cooked mode, adds a LineFeed
 * following a final CarriageReturn. If BufAddr=0, sets TTYMode from Mode
 * parameter (range 0..3); otherwise, the Mode parameter is not used.
 */
void DoTTYWrite(int TermNum, char * BufAddr, int NumCharsToWrite, int Mode) {

	if(BufAddr == 0)
		SetTTYMode(TermNum,Mode);
	else  {
		int CharsLeft;
        char OutChar, LastChar;
        
        CharsLeft = NumCharsToWrite ;
		OutChar = *BufAddr ;
		LastChar = OutChar;

		while( (CharsLeft > 0) && (OutChar != CH_NUL) ) {

			if( CookedMode[TermNum] && OutChar == '\r') {
				OutputChar(TermNum,'\n') ; //LineFeed
	  		}

	  		OutputChar(TermNum,OutChar);	//put char in output buffer

			CharsLeft-- ;
			LastChar = OutChar ;
			BufAddr++ ;
			OutChar = *BufAddr ;	//fetch next char from OS buffer

		} /*end while*/
	}

} /*end DoTTYWrite()*/


/*---------------------------------------------------------------------*/
/* Process body for the Top half of the Output Half of the TTY Driver
 * The driver expects to receive its input and return Mailbox ID's
 * and its "Terminal Number" as part of its "Initial Environment".
 */
void TTYWrite (int IORequestMailboxID, int IOResponseMailboxID, int TerminalNum) {

    InitTTY (TerminalNum);     /* initialize the serial port for this terminal */

	while(1){
        int senderPID;
        int MW1, MW2, MW3, MW4, MW5, MW6;
        
        RECEIVE(IORequestMailboxID, senderPID, MW1, MW2, MW3, MW4, MW5, MW6);
        
        
		//Receive an IORequest message containing a Buffer Address, number of characters
		//	to write, and a TTYMode ;

		DoTTYWrite (TerminalNum, MW1, MW2, MW3);
        
        SEND(IOResponseMailboxID, senderPID, MW2, 0, 0, 0, 0, 0);
		//Send an IOResponse message back to the original requestor giving
		//  the number of characters written ;
    }

} /* end TTYWrite process */


/*=====================================================================*/
/*   Code modules for the TTY Input Driver                            */
/*=====================================================================*/


/* This routine reads chars from a terminal into the specified buffer */
void DoTTYRead (int TermNum, char * BufferAddr, int *NumCharsReturned) {
    char InChar, backspace, escape;
    backspace = 0x08;
    escape = 0x1b;
	*NumCharsReturned = 0;
    
	do {
		//wait for a character
		//Execute a WAIT trap, specifying the InputAvailable semaphore for TermNum;
        WAIT(inputDataAvailSemaphores[TermNum]);
        
		//protect queue from simultaneous accesses
		DI();  //disable interrupts

		//get a character from this terminal's input queue
		InChar = GetCharFromInputQueue(TermNum);

		//restore interrupt state
		EI();

		//process the input char
		if ((CookedMode[TermNum]) && (InChar == backspace)) {

			//the terminal is in "cooked" mode; process the backspace by
			// deleting the previous character from the buffer (if there is one)
			if (*NumCharsReturned > 0) {
				*NumCharsReturned = (*NumCharsReturned) - 1 ;
				BufferAddr -- ;
				//delete the character on the screen also by overwriting it with a space
				InsertIntoEchoQueue(TermNum,backspace);	//output a BS to the terminal
				InsertIntoEchoQueue(TermNum, ' '); 		//output a Space (overwrite previous char)
				InsertIntoEchoQueue(TermNum, backspace);	//move cursor back to the space
			}

		} else {
			/*the terminal is either in Raw mode or InChar in NOT a backspace (or both);
				either way, add InChar to the buffer ; */
			*BufferAddr = InChar ;
			BufferAddr ++ ;
			*NumCharsReturned += 1 ;
		}
    }
	while (  (InChar != '\n')			//check for End-of-line flags
				&& (InChar != escape)
				&& (*NumCharsReturned < BUFFER_SIZE - 1)
				&& (CookedMode[TermNum])) ;				//quit after 1 char in cooked mode

	/*if cooked mode, add CR (carraiage-return) if not already present */
	if ( (InChar != '\n') && CookedMode[TermNum] ) {
		*BufferAddr = '\n' ;
		*NumCharsReturned += 1 ;
	}
} //end of DoTTYRead


/*---------------------------------------------------------------------*/
/* Process body for the Top Half of the Input Half of the TTY Driver.
 * The driver expects to receive its input and return Mailbox ID's
 * and its "Terminal Number" as part of its "Initial Environment".
 */
void TTYRead (int IORequestMBid, int IOResultMBid, int TermNum) {

  /* wait for the Output driver to initialize the TTY channel */
	WAIT(initDoneSemaphores[TermNum]);

	while(1) {
        int senderPID;
        int NumCharsReturned;
        int MW1, MW2, MW3, MW4, MW5, MW6;
        
        RECEIVE(IORequestMBid, senderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		//Receive an IORequest message containing a Buffer Address ;
		DoTTYRead (TermNum, MW1, &NumCharsReturned);
    
        SEND(IOResultMBid, senderPID, NumCharsReturned, 0, 0, 0, 0, 0);
		//Send an IOResponse message back to the original requestor giving
		// the number of characters read from the keyboard ;
	}
}


/*-------------------------------------------------------*/
/* TTY Driver Bottom-Half Interrupt Service Routine     */

//TTY keyboard ISR
void GetChar (int TermNum) {
    char ErrorStatus;
    char InChar;
	// read and save serial port error status (also clears any errors)
	ErrorStatus = inportb( baseIO[TermNum] + LSR ) ;	//5 = Line Status Register

	// read serial port data register, mask out parity bit
	InChar = inportb( baseIO[TermNum] ) & 0x7F  ;

	// check for framing, parity, or overrun errors
	if ( (ErrorStatus & 0xE) != 0 ) {
		InChar = '?' ;	//an error occurred; replace input with '?'
	}

	if (IsQueueFull(&inqueue[TermNum])){

		InsertIntoEchoQueue(TermNum, 0x07);		//echo 'BELL' char
    }
	else {

		InsertIntoInputQueue(TermNum,InChar);		//add input char to raw queue

		// Invoke Kernel routine to signal appropriate semaphore.
		//  Note that this is NOT a Trap (Int instruction)...
		SemaphorePost(inputDataAvailSemaphores[TermNum]);
        //KernelServices.Signal(Input Available Semaphore for TermNum) ;

		// echo char as appropriate
		if (EchoMode[TermNum]) {
            //Echo mode is ON for TermNum
			if (InChar >= 0x20) {
                //InChar is printable ASCII
				InsertIntoEchoQueue(TermNum,InChar) ;
			} else if (InChar == '\r') {
				//echo CR as CR/LF
				InsertIntoEchoQueue(TermNum, InChar);
				InsertIntoEchoQueue(TermNum, '\n');
			} else {
				// echo control chars as ^X (i.e., '^' followed by printable char
				InsertIntoEchoQueue (TermNum, '^');
				InsertIntoEchoQueue (TermNum, (InChar|0x40)) ;	//0x40 forces Uppercase
			}
		}
	}
} //end of GetChar
