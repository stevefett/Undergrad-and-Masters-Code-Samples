#include <spede/stdio.h>
#include <spede/flames.h>
#include "OSAPI.h"
#include "producerconsumer.h"

// int boundedBuffer[10][10];

void Producer(int delay, int spaceAvailSemID, int dataAvailSemID, int lineNum)
{
	int bufferIndex = 0;
	char nextChar = 'a';
	
	while (1)
	{
		cons_gotoRC(lineNum, 78);
		cons_putchar(nextChar);
		WAIT(spaceAvailSemID);
		if ((lineNum % 2) == 0)
		{
			boundedBuffer[0][bufferIndex] = nextChar;
		}
		else
		{
			boundedBuffer[1][bufferIndex] = nextChar;
		}
		bufferIndex = (bufferIndex + 1) % 10;
		SIGNAL(dataAvailSemID);
		SLEEP(delay);
		nextChar = nextChar + 1;
		if (nextChar > 'z')
		{
			nextChar = 'a';
		}
	}
}
