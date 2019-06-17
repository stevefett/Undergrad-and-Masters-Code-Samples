#include <spede/stdio.h>
#include <spede/flames.h>
#include "OSAPI.h"
#include "producerconsumer.h"

void Consumer(int delay, int spaceAvailSemID, int dataAvailSemID, int lineNum)
{
	char nextChar;
	int bufferIndex = 0;
	while (1)
	{
		WAIT(dataAvailSemID);
		if ((lineNum % 2) == 0)
		{
			nextChar = boundedBuffer[0][bufferIndex];
		}
		else
		{
			nextChar = boundedBuffer[1][bufferIndex];
		}
		SIGNAL(spaceAvailSemID);
		bufferIndex = (bufferIndex + 1) % 10;
		cons_gotoRC(lineNum, 78);
		cons_putchar(nextChar);
		SLEEP(delay);
		cons_gotoRC(lineNum, 78);
		cons_putchar(' ');
		SLEEP(delay);
	}
}

