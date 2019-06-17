#include <spede/stdio.h>
#include <spede/flames.h>

extern int flicker3(void);
int delay3 (void);
int toggle3 (void);
char toggle3Char;

int delay3(void)
{
	int delayCount = 0;
	while (delayCount <= 100000)
	{
		IO_DELAY();
		delayCount++;
	}
	return 0;
}

int toggle3(void)
{
	DI();
	if (toggle3Char != 32)
		toggle3Char = 32;
	else
		toggle3Char = 82;
	cons_gotoRC(0,79);
	cons_putchar(toggle3Char);
	EI(); 
	delay3();
	return 0;	
}

extern int flicker3(void)
{
	while (1)
	{
		delay3();
		toggle3();
	}

	return 0;
}


