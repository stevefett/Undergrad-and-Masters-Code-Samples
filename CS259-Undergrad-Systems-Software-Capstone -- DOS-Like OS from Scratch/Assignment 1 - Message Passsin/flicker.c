#include <spede/stdio.h>
#include <spede/flames.h>
#include "OSAPI.h"

void Flicker (int onTime, int offTime, int mutexSemID, int lineNum)
{
	while (1)
	{
		WAIT(mutexSemID);
		cons_gotoRC(lineNum, 78);
		cons_putchar('f');
		SLEEP(onTime);
		cons_gotoRC(lineNum, 78);
		cons_putchar(' ');
		SIGNAL(mutexSemID);
		SLEEP(offTime);
	}
}
		
	
