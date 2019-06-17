#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker7(void);
int delay7 (void);
int toggle7 (void);
char toggle7Char;

int delay7(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle7(void)
{
	DI();
	if (toggle7Char != 32)
		toggle7Char = 32;
	else
		toggle7Char = 66;
	cons_gotoRC(24,0);
	cons_putchar(toggle7Char);
	EI(); 
	delay7();
	return 0;	
}

extern int flicker7(void)
{
	while (1)
	{
		delay7();
		toggle7();
	}

	return 0;
}


