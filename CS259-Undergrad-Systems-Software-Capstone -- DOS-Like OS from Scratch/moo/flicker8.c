#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker8(void);
int delay8 (void);
int toggle8 (void);
char toggle8Char;

int delay8(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle8(void)
{
	DI();
	if (toggle8Char != 32)
		toggle8Char = 32;
	else
		toggle8Char = 66;
	cons_gotoRC(24,40);
	cons_putchar(toggle8Char);
	EI(); 
	delay8();
	return 0;	
}

extern int flicker8(void)
{
	while (1)
	{
		delay8();
		toggle8();
	}

	return 0;
}


