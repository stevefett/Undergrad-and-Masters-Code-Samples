#include <spede/stdio.h>
#include <spede/flames.h>

extern int idle(void);
int delayIdle (void);
int toggleIdle (void);
char toggleIdleChar;

int delayIdle(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggleIdle(void)
{
	DI();
	if (toggleIdleChar != 32)
		toggleIdleChar = 32;
	else
		toggleIdleChar = 73;
	cons_gotoRC(24,40);
	cons_putchar(toggleIdleChar);
	EI(); 
	delayIdle();
	return 0;	
}

extern int idle(void)
{
	while (1)
	{
		delayIdle();
		toggleIdle();
	}

	return 0;
}


