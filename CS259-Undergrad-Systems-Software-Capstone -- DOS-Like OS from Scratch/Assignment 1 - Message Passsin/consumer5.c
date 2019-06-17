#include <spede/stdlib.h>
#include <spede/string.h>
#include "kerneldata.h"
#include "OSAPI.h"

void Consumer5 (int ConsumerMailboxID, int Delay, int ScreenLocation)
{
	char NextChar;
	int CurrentColumn;
	int CurrentRow;
	int BottomRow;
	int MW1;
	int MW2;
	int MW3;
	int MW4;
	int MW5;
	int MW6;
	int BufferID;
	int senderPID;
	int index;

	index = 0;
  	CurrentColumn = 0 ;
  	if (ScreenLocation == 0) 
		 CurrentRow = 0;
	else 
		CurrentRow = 13 ;
  	BottomRow = CurrentRow + 11;
  	while(1) 
	{
      		SLEEP (Delay) ; // each process gets its own IE “Delay” time
      		
		RECEIVE(ConsumerMailboxID, senderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		BufferID = MW1;
      		NextChar = globalBuffers[BufferID][index++];
      		while (NextChar != '\r') 
		{
        		WAIT (ConsoleScreenAvailSemaphore) ; // make sure no one else is using screen
         		cons_gotoRC (CurrentRow,CurrentColumn); // move cursor to proper row/col
         		cons_putchar (NextChar) ;                  // display the character
         		SIGNAL (ConsoleScreenAvailSemaphore) ; // allow someone else to use screen
         		CurrentColumn++ ;                         // move to the next screen column
         		if (CurrentColumn > 70)
			{                  // check for end of available line space
             			CurrentColumn = 0 ;                    // end of line reached; move to next line
             			CurrentRow++ ;
            			if (CurrentRow > BottomRow) 
				{       //check for wraparound to first line
                			CurrentRow = BottomRow - 11 ;
             			}
         		}
         		
      		} //end while not-end-of-string
		memset(globalBuffers[BufferID], '\0', BUFFER_SIZE);
      		SEND(FreeBufferMailboxID, 0, BufferID, MW2, MW3, MW4, MW5, MW6); 
  	} //end loop
}
