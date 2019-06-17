#include <spede/machine/parallel.h>
#include <spede/machine/io.h>
#include "kerneldata.h"
#include "OSAPI.h"

void init_printer(){
    outportb(LPT1_BASE + LPT_CONTROL, PC_SLCTIN | PC_INIT | PC_IRQEN);
    SIGNAL(PRINTER_SEMAPHORE);
}

void parallel_strobe(){
    char currentControlRegister;
    
    currentControlRegister = inportb(LPT1_BASE + LPT_CONTROL);
    outportb(LPT1_BASE + LPT_CONTROL, currentControlRegister | PC_STROBE);
    IO_DELAY();
    IO_DELAY();
    outportb(LPT1_BASE + LPT_CONTROL, currentControlRegister);
    }

void write_char(char ch){
    if((inportb(LPT1_BASE + LPT_STATUS) & PS_SLCT)){
        outportb(LPT1_BASE + LPT_DATA, ch);
        parallel_strobe();
    }
}

void send_buffer_to_printer(char *printBuffer){
    
    char nextChar;
    WAIT(PRINTER_SEMAPHORE);
    
    nextChar = *printBuffer;
    while(nextChar != '\0'){
        if(nextChar == '\n'){
            write_char('\r');
            WAIT(PRINTER_SEMAPHORE);
        }
        write_char(nextChar);
        printBuffer++;
        nextChar = *printBuffer;
        WAIT(PRINTER_SEMAPHORE);
    }
    SIGNAL(PRINTER_SEMAPHORE);
}
void PrinterDriver(int IORequestMailboxID, int IOResultMailboxID){

    init_printer();
    
    while(1){
        int senderID;
        int MW1, MW2, MW3, MW4, MW5, MW6;
        RECEIVE(IORequestMailboxID, senderID, MW1, MW2, MW3, MW4, MW5, MW6);
        send_buffer_to_printer(MW1);
        SEND(IOResultMailboxID, senderID, MW1, MW2, MW3, MW4, MW5, MW6);
    }
}
