#include <spede/stdio.h>
#include <spede/flames.h>
#include <spede/ctype.h>
#include "kerneldata.h"

PCBListPtr pcbLists[NUM_OF_PCB_LISTS];
bool DONE = FALSE;
int i;

char processPromptString[45] = "How many processes should be created (1-9): \0";
char processErrorString[66] = "Invalid Input. Please enter a number between 1 and 9, inclusive: \0";

int numOfProcesses = 0;
char* prompt  = processPromptString;
bool validInput = FALSE;

void InitOS(){

    CreatePCBLists();
    
    // Prompt for number of processes to create
    while(!validInput){
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
    
    // Create Processes
    CreateProcess(pcbLists[IDLE_LIST]);
    for(i = 0; i < numOfProcesses; i++){
        CreateProcess(pcbLists[READY_LIST]);		
    }
}

void Dispatcher(){

    while(!DONE){
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
        cons_printf("%d", GetRunningPID());
        if(cons_kbhit()){
            ENTRY(0x20);
        }
    }
}

int main(){

    InitOS();
    Dispatcher();
    
    return 0;
}
