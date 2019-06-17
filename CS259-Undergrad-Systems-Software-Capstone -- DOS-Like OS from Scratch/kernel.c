#include <spede/stdio.h>
#include <spede/stdlib.h>
#include <spede/flames.h>
#include <spede/ctype.h>
#include "kerneldata.h"
#include "EnterProcess.h"
#include "interrupt.h"
#include "idle.h"
#include "flicker1.h"
#include "flicker2.h"
#include "flicker3.h"
#include "flicker4.h"
#include "flicker5.h"
#include "flicker6.h"
#include "flicker7.h"
#include "flicker8.h"

PCBListPtr pcbLists[NUM_OF_PCB_LISTS];
bool DONE = FALSE;
int i;

int Kernel_Stack[1000];

//char processPromptString[45] = "How many processes should be created (1-9): \0";
//char processErrorString[66] = "Invalid Input. Please enter a number between 1 and 9, inclusive: \0";

//int numOfProcesses = 0;
//char* prompt  = processPromptString;
//bool validInput = FALSE;

void InitOS(){

    CreatePCBLists();
//    Kernel_Stack = (int*)malloc(4000);
    // Prompt for number of processes to create
  /*  while(!validInput){
        cons_putstr(prompt);
        numOfProcesses = cons_getchar();
        if(numOfProcesses < '1' || numOfProcesses > '9'){
            prompt = processErrorString;
        }
        else{
            numOfProcesses -= '0';
            validInput = TRUE;
        }
    }
    */
    // Create Processes
    CreateProcess(pcbLists[IDLE_LIST], &idle);
        CreateProcess(pcbLists[READY_LIST], &flicker1);
	CreateProcess(pcbLists[READY_LIST], &flicker2);
        CreateProcess(pcbLists[READY_LIST], &flicker3);
        CreateProcess(pcbLists[READY_LIST], &flicker4);
        CreateProcess(pcbLists[READY_LIST], &flicker5);
        CreateProcess(pcbLists[READY_LIST], &flicker6);
        CreateProcess(pcbLists[READY_LIST], &flicker7);
        CreateProcess(pcbLists[READY_LIST], &flicker8);
		
}

void Dispatcher(){
	TrapFrame *moocow;
        if(IsEmpty(pcbLists[RUNNING_LIST])){
            if(IsEmpty(pcbLists[READY_LIST])){
                TransferHeadPCB(pcbLists[IDLE_LIST], pcbLists[RUNNING_LIST]);
            }
            else{
                TransferHeadPCB(pcbLists[READY_LIST], pcbLists[RUNNING_LIST]);
            }
        }
        else if(GetRunningPID() == 0 && !IsEmpty(pcbLists[READY_LIST])){
            TransferHeadPCB(pcbLists[RUNNING_LIST], pcbLists[IDLE_LIST]);
            TransferHeadPCB(pcbLists[READY_LIST], pcbLists[RUNNING_LIST]);
        }
    
	IRQEnable(0x0);
	moocow = pcbLists[RUNNING_LIST]->head->next->data->TrapFramePtr;
	EnterProcess (moocow);
}

int main(){

    InitOS();
    Dispatcher();
    
    return 0;
}
