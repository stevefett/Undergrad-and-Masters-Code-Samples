#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker4(void);
int delay4 (void);
int toggle4 (void);
char toggle4Char;

int delay4(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle4(void)
{
	DI();
	if (toggle4Char != 32)
		toggle4Char = 32;
	else
		toggle4Char = 108;
	cons_gotoRC(12,0);
	cons_putchar(toggle4Char);
	EI(); 
	delay4();
	return 0;	
}

extern int flicker4(void)
{
	while (1)
	{
		delay4();
		toggle4();
	}

	return 0;
}


