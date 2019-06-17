#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker5(void);
int delay5 (void);
int toggle5 (void);
char toggle5Char;

int delay5(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle5(void)
{
	DI();
	if (toggle5Char != 32)
		toggle5Char = 32;
	else
		toggle5Char = 109;
	cons_gotoRC(12,40);
	cons_putchar(toggle5Char);
	EI(); 
	delay5();
	return 0;	
}

extern int flicker5(void)
{
	while (1)
	{
		delay5();
		toggle5();
	}

	return 0;
}
