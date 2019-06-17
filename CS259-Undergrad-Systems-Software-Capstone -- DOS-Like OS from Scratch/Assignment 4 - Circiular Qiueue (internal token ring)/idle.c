#include <spede/stdio.h>
#include <spede/flames.h>
#include "idle.h"

int idle(void);
int delayIdle (void);
int toggleIdle (void);
char toggleIdleChar = 0;

int delayIdle(void)
{
    int delayCount = 0;
    while (delayCount <=  FLICKER_COUNT)
    {
        IO_DELAY();
        delayCount++;
    }
    return 0;
}

int toggleIdle(void)
{
    DI();
    if (toggleIdleChar != ' ')
    toggleIdleChar = ' ';
    else
    toggleIdleChar = 'I';
    cons_gotoRC(24,78);
    cons_putchar(toggleIdleChar);
    EI();
    delayIdle();
    return 0;	
}

int idle(void)
{
    toggleIdle();
    while (1)
    {
        delayIdle();
        toggleIdle();
    }

    return 0;
}


