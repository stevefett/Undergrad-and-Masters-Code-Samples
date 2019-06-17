#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker6(void);
int delay6 (void);
int toggle6 (void);
char toggle6Char;

int delay6(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle6(void)
{
	DI();
	if (toggle6Char != 32)
		toggle6Char = 32;

	else
		toggle6Char = 114;
	cons_gotoRC(12,79);
	cons_putchar(toggle6Char);
	EI(); 
	delay6();
	return 0;	
}

extern int flicker6(void)
{
	while (1)
	{
		delay6();
		toggle6();
	}

	return 0;
}


