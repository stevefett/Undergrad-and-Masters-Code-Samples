#include "OSAPI.h"
#include "flicker.h"
#include "producerconsumer.h"
#include "init.h"
#include "printerdriver.h"
#include "kerneldata.h"
#include "spooler.h"
#include "TTYDriver.h"
#include "talk.h"

int init(){

    int i;
    int tty1ReadPid, tty1WritePid, tty2ReadPid, tty2WritePid;
    for(i =0; i < MAX_BUFFERS; i++){
        SEND(FREE_BUFFER_MAILBOXID, 0, globalBuffers[i], 0, 0, 0, 0, 0);
    }
    
    SPAWN(&Flicker, initialDelayValues[0], initialDelayValues[1], 0, 0);
    SPAWN(&Flicker, initialDelayValues[2], initialDelayValues[3], 0, 1);
    SPAWN(&Flicker, initialDelayValues[4], initialDelayValues[5], 1, 5);
    SPAWN(&Flicker, initialDelayValues[6], initialDelayValues[7], 1, 6);
    SPAWN(&Producer, initialDelayValues[8], 2, 3, 18);
    SPAWN(&Consumer, initialDelayValues[9], 2, 3, 19);
    
    SPAWN(&PrinterDriver, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, initialDelayValues[12], 0);
    SPAWN(&PrintSpooler, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, pcbLists[ACTIVE_LIST]->head->active->data->pid, 1);
    
    SPAWN(&TTYWrite, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, 1, 0);
    tty1WritePid = pcbLists[ACTIVE_LIST]->head->active->data->pid;
    SPAWN(&TTYWrite, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, 2, 0);
    tty2WritePid = pcbLists[ACTIVE_LIST]->head->active->data->pid;
    SPAWN(&TTYRead, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, 1, 0);
    tty1ReadPid = pcbLists[ACTIVE_LIST]->head->active->data->pid;
    SPAWN(&TTYRead, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, 2, 0);
    tty2ReadPid = pcbLists[ACTIVE_LIST]->head->active->data->pid;
    
    SPAWN(&Talk, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, 1, 2);
    SPAWN(&Talk, IO_REQUEST_MAILBOXID, IO_RESULT_MAILBOXID, 2, 1);
    
    SPAWN(&Producer5, CONSUMER_MAILBOXID, initialDelayValues[13], 0, 0);
    SPAWN(&Consumer5, CONSUMER_MAILBOXID, initialDelayValues[14], TOP, 0);
    SPAWN(&Consumer5, CONSUMER_MAILBOXID, initialDelayValues[15], BOTTOM, 0);
    
    
    while(1){
        cons_gotoRC(8, 78);
		cons_putchar('i');
		SLEEP(5);
		cons_gotoRC(8, 78);
		cons_putchar(' ');
		SLEEP(5);
    }
}
