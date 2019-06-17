#include <spede/stdio.h>
#include <spede/flames.h>
#include "kerneldata.h"

int Kernel_Stack;
bool DEBUG = TRUE;

void TimesliceHandler(){
    //printf("Timeslice interrupt\n");
    int cur_pid = GetRunningPID();
    //printf("Got pid %d \n", cur_pid);
    if (cur_pid > 0){
        TransferPCB(cur_pid, pcbLists[RUNNING_LIST], pcbLists[READY_LIST]);
    }
    else if (cur_pid == 0){
        TransferPCB(cur_pid, pcbLists[RUNNING_LIST], pcbLists[IDLE_LIST]);
    }
    else{
        printf("Error: There are no current running processes.\n");
    }
}

void SleepHandler(){
    //printf("Sleep interrupt\n");
    int cur_pid = GetRunningPID();
    if (cur_pid > 0){
        TransferPCBByPriority(GetHeadPriority(pcbLists[RUNNING_LIST]), pcbLists[RUNNING_LIST], pcbLists[SLEEP_LIST]);
    }
    else if (cur_pid == 0){
        printf("Error: Cannot put the idle process to sleep.\n");
    }
    else{
        printf("Error: There are no current running processes.\n");
    }
}

void AwakenHandler(){
    //printf("Awaken interrupt\n");
    if (!IsEmpty(pcbLists[SLEEP_LIST]))
    {	
        int pid = GetHeadPID(pcbLists[SLEEP_LIST]);				
        TransferPCB(pid, pcbLists[SLEEP_LIST], pcbLists[READY_LIST]);
    }
    else{
        printf("Error: There are no processes currently on the sleep list.\n");
    }
}

void SBlockHandler(){
    //printf("SBlock process\n");
    int cur_pid = GetRunningPID();
    if (cur_pid > 0)
    {
        char key = cons_getchar();
        switch (key)
        {
        case '1':
            TransferPCB(cur_pid, pcbLists[RUNNING_LIST], pcbLists[S1BLOCKED_LIST]);
            break;
        case '2':
            TransferPCB(cur_pid, pcbLists[RUNNING_LIST], pcbLists[S2BLOCKED_LIST]);
            break;
        default:
            break;
        }
    }	
    else{
        printf("Error: Cannot block the idle process.\n");
    }
}

void SUnblockHandler(){
    //printf("Unblock process\n");
    char key = cons_getchar();
    switch (key)
    {
    case '1':
        if (!IsEmpty(pcbLists[S1BLOCKED_LIST])){
            TransferHeadPCB(pcbLists[S1BLOCKED_LIST], pcbLists[READY_LIST]);
        }
        else{
            printf("Error: S1Blocked list is empty.\n");
        }
        break;
    case '2':
        if (!IsEmpty(pcbLists[S2BLOCKED_LIST])){
            TransferHeadPCB(pcbLists[S2BLOCKED_LIST], pcbLists[READY_LIST]);
        }
        else{
            printf("Error: S2Blocked list is empty.\n");
        }
        break;
    default:
        break;
    }
}

void MBlockHandler(){
    //printf("MBlock process\n");
    int cur_pid = GetRunningPID();
    if (cur_pid > 0)
    {
        char key = cons_getchar();
        switch (key)
        {
        case '1':
            TransferPCB(cur_pid, pcbLists[RUNNING_LIST], pcbLists[M1BLOCKED_LIST]);
            break;
        case '2':
            TransferPCB(cur_pid, pcbLists[RUNNING_LIST], pcbLists[M2BLOCKED_LIST]);
            break;
        default:
            break;
        }
    }
    else if(cur_pid == 0){
        printf("Error: Cannot block the idle process\n");
    }
    else{
        printf("Error: There are no current running processes.\n");
    }
}

void MUnblockHandler(){
    //printf("Remove blocked to ready\n");
    char key = cons_getchar();
    switch (key)
    {
    case '1':
        key = cons_getchar();
        if (key >= '1' && key <= '9')
        {
            key -= '0';
            if(TransferPCBByPID(key, pcbLists[M1BLOCKED_LIST], pcbLists[READY_LIST]) == -1){
                printf("Pid: %d is not on M1BLOCKED_LIST.\n", key);
            }
        }
        else{
            printf("ProcessID must be between 1 and 9.\n");	
        }
        break;
    case '2':
        key = cons_getchar();
        if (key >= '1' && key <= '9')
        {
            key -= '0';
            if(TransferPCBByPID(key, pcbLists[M2BLOCKED_LIST], pcbLists[READY_LIST]) == -1){
                printf("Pid: %d is not on M2BLOCKED_LIST.\n", key);
            }
        }
        else{
            printf("ProcessID must be between 1 and 9.\n");	
        }
        break;
    default:
        break;
    }
}

void ServiceInterrupt(TrapFrame* frame)
{
	int my_trapno;
	(((pcbLists[RUNNING_LIST]->head)->next)->data)->ProcessStackPointer = frame;
	my_trapno = frame->trapno;
	switch (my_trapno)
	{
			case 0x20:
				TimesliceHandler();
				break;
			default:
				printf("Unhandled exception %d!", my_trapno);
				exit(1);

	}
	Dispatcher();
}

void TimerISR(){

	
	if (cons_kbhit())
	{
   
    		char key = cons_getchar();
    		switch (key)
    		{
    			case 't':
        			TimesliceHandler();
        			break;
    			case 'z':
        			SleepHandler();
       				break;
    			case 'a':
        			AwakenHandler();
        			break;
    			case 'w':
        			SBlockHandler();
        			break;
    			case 's':
        			SUnblockHandler();
        			break;
    			case 'm':
        			MUnblockHandler();
        			break;
    			case 'r':
        			MBlockHandler();
        			break;
    			case '1':
        			printf("Walk the active list:\n");
        			DisplayPCBList(pcbLists[ACTIVE_LIST]);					
        			break;
    			case '2':
        			printf("Walk the ready list:\n");
        			DisplayPCBList(pcbLists[READY_LIST]);
        			break;
    			case '3':
        			printf("Walk the sleep list:\n");
        			DisplayPCBList(pcbLists[SLEEP_LIST]);
        			break;
    			case '4':
        			printf("Walk the S1Blocked list:\n");
        			DisplayPCBList(pcbLists[S1BLOCKED_LIST]);
        			break;
    			case '5':
        			printf("Walk the S2Blocked list:\n");
        			DisplayPCBList(pcbLists[S2BLOCKED_LIST]);
        			break;
    			case '6':
        			printf("Walk the M1Blocked list:\n");
        			DisplayPCBList(pcbLists[M1BLOCKED_LIST]);
        			break;
    			case '7':
        			printf("Walk the M2Blocked list:\n");
        			DisplayPCBList(pcbLists[M2BLOCKED_LIST]);
        			break;	

    			case 'd':
        			DEBUG = !DEBUG;
        			if (DEBUG)
        				printf("Debugging enabled.\n");
        			else
        				printf("Debugging disabled.\n");
        			break;
    			case 'q':
        			DONE = TRUE;
        			break;
    			default:
        			printf("Invalid input, please try again.\n");
	}	    
    }
    else
    {
		TimesliceHandler();		
    }
}

