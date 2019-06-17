#include "OSAPI.h"
#include "flicker.h"
#include "producerconsumer.h"
#include "init.h"

int init(){
    
    SPAWN(&Flicker, initialDelayValues[0], initialDelayValues[1], 0, 0);
    SPAWN(&Flicker, initialDelayValues[2], initialDelayValues[3], 0, 1);
    SPAWN(&Flicker, initialDelayValues[4], initialDelayValues[5], 1, 5);
    SPAWN(&Flicker, initialDelayValues[6], initialDelayValues[7], 1, 6);
    SPAWN(&Producer, initialDelayValues[8], 2, 3, 18);
    SPAWN(&Consumer, initialDelayValues[9], 2, 3, 19);
    SPAWN(&Producer, initialDelayValues[10], 4, 5, 21);
    SPAWN(&Consumer, initialDelayValues[11], 4, 5, 22);
    
    while(1){
        cons_gotoRC(8, 78);
		cons_putchar('i');
		SLEEP(5);
		cons_gotoRC(8, 78);
		cons_putchar(' ');
		SLEEP(5);
    }
}
