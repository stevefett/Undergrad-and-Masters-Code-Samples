#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker1(void);
int delay1 (void);
int toggle1 (void);
char toggle1Char;

int delay1(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle1(void)
{
	DI();
	if (toggle1Char != 32)
		toggle1Char = 32;
	else
		toggle1Char = 76;
	cons_gotoRC(0,0);
	cons_putchar(toggle1Char);
	EI(); 
	delay1();
	return 0;	
}

extern int flicker1(void)
{
	while (1)
	{
		delay1();
		toggle1();
	}

	return 0;
}


