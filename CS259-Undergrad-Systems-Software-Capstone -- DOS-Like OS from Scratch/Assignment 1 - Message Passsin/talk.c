#include <spede/stdlib.h>

void Talk(int IORequestMailBox, int IOResultMailBox, int TTYReadPID, int TTYWritePID)
{
	int BufferID;
	int SenderPID;
	int MW1;
	int MW2;
	int MW3;
	int MW4;
	int MW5;
	int MW6;
	while(1)
	{
		RECEIVE(FreeBufferMailboxID, SenderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		BufferID = MW1;
		SEND(IORequestMailBox, TTYReadPID, BufferID, MW2, MW3, MW4, MW5, MW6);
		RECEIVE(IOResultMailBox, SenderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		SEND(IORequestMailBox, TTYWritePID, BufferID, MW2, MW3, MW4, MW5, MW6);	
		RECEIVE(IOResultMailBox, SenderPID, MW1, MW2, MW3, MW4, MW5, MW6);
		memset(globalBuffers[BufferID], '\0', BUFFER_SIZE);
      		SEND(FreeBufferMailboxID, 0, BufferID, MW2, MW3, MW4, MW5, MW6);	
	}
}
