#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker2(void);
int delay2 (void);
int toggle2 (void);
char toggle2Char;

int delay2(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle2(void)
{
	DI();
	if (toggle2Char != 32)
		toggle2Char = 32;
	else
		toggle2Char = 77;
	cons_gotoRC(0,40);
	cons_putchar(toggle2Char);
	EI(); 
	delay2();
	return 0;	
}

extern int flicker2(void)
{
	while (1)
	{
		delay2();
		toggle2();
	}

	return 0;
}


