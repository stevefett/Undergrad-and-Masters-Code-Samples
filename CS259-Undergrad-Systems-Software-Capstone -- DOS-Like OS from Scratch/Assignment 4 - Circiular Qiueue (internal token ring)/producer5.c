#include "OSAPI.h"
#include "kerneldata.h"
#include <spede/stdlib.h>
#include <spede/stdio.h>

void Producer5 (int ConsumerMailboxID, int P5Delay) 
{
	int LineNum;
	int MW1;
	int MW2;
	int MW3;
	int MW4;
	int MW5;
	int MW6;
	int senderPID;
	int BufferID;
	char ascii[16];
	LineNum = 1;
	

	while(1); 
	{
     		
		RECEIVE(FreeBufferMailboxID, senderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		BufferID = MW1;  
		sprintf(ascii, "%d", LineNum); 		
		sprintf((char *)globalBuffers[BufferID], "%s %s%c", "No Name OS", 
			ascii, '\r');     	
		SEND(ConsumerMailboxID, 0, BufferID, MW2, MW3, MW4, MW5, MW6);     			
     		SLEEP (P5Delay) ;
     		LineNum++;
  	} //end loop
}