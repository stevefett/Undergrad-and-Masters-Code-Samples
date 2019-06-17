#include <spede/stdlib.h>
#include "OSAPI.h"
#include "spooler.h"

void PrintSpooler(int IORequestMailBoxID, int IOResultMailBoxID, int PrinterDriverPID, int delay)
{
	int LineNum;
	int MW1;
	int MW2;
	int MW3;
	int MW4;
	int MW5;
	int MW6;
	int SenderPID;
	int BufferID;
	char ascii[16];

	LineNum = 1;

	while(1)
	{
		RECEIVE(FreeBufferMailboxID, senderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		BufferID = MW1;
		BufferID = MW1;  
		sprintf(ascii, "%d", LineNum); 		
		sprintf((char *)globalBuffers[BufferID], "%s %s%c", "No Name OS", 
			ascii, '\r');     	
		SEND(IORequestMailBoxID, PrinterDriverPID, BufferID, MW2, MW3, MW4, MW5, MW6);
		RECEIVE(IOResponseMailBoxID, senderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		memset(globalBuffers[BufferID], '\0', BUFFER_SIZE);
      		SEND(FreeBufferMailboxID, 0, BufferID, MW2, MW3, MW4, MW5, MW6);
		SLEEP(delay);
		LineNum++;
	}
}
