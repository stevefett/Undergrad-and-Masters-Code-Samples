#include <spede/stdio.h>
#include <spede/flames.h>
#include <spede/machine/pic.h>
#include <spede/machine/io.h>
#include <spede/time.h>
#include "kerneldata.h"


bool DEBUG = TRUE;

void DisplaySemaphores();

void IRQAck(unsigned IRQ)
{
    if (IRQ >= 8)
    {
        outportb(0x20, SPECIFIC_EOI(IRQ_CASCADE));
        outportb(0xA0, SPECIFIC_EOI(IRQ-8));
    }
    else{
        outportb(0x20, SPECIFIC_EOI(IRQ));
    }
}

void IRQEnable(unsigned IRQ)
{
    if (IRQ >= 8)
    {
        outportb(0x21, inportb(0x21) & ~BIT(IRQ_CASCADE));
        outportb(0xA1, inportb(0xA1) & ~BIT(IRQ - 8));
    }
    else{
        outportb(0x21, inportb(0x21) & ~BIT(IRQ));
    }
}

void TimesliceHandler(){
     int cur_pid = GetRunningPID();
     //printf("Timeslice interrupt\n");
   
    //printf("Got pid %d \n", cur_pid);
     if((ELAPSED_TICKS % 1000) == 0){
       printf("Elapsed Ticks: %d\n", ELAPSED_TICKS);
     }
     while((!IsEmpty(pcbLists[SLEEP_LIST])) && (GetHead(pcbLists[SLEEP_LIST])->data->wakeTime <= ELAPSED_TICKS)){
	     TransferHeadPCB(pcbLists[SLEEP_LIST], pcbLists[READY_LIST]);
	   }
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

// void SleepHandler(){
    //printf("Sleep interrupt\n");
    // int cur_pid = GetRunningPID();
    // if (cur_pid > 0){
        // TransferPCBByPriority(GetHeadPriority(pcbLists[RUNNING_LIST]), pcbLists[RUNNING_LIST], pcbLists[SLEEP_LIST]);
    // }
    // else if (cur_pid == 0){
        // printf("Error: Cannot put the idle process to sleep.\n");
    // }
    // else{
        // printf("Error: There are no current running processes.\n");
    // }
// }

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

void GetPIDISR(TrapFramePtr frame)
{
	frame->eax = GetRunningPID();
}

void SleepISR(TrapFramePtr frame)
{
	int wakeTime;
	int sleepTime;
	sleepTime = frame->eax;
	wakeTime = (CLK_TCK * sleepTime) + ELAPSED_TICKS;
    GetHead(pcbLists[RUNNING_LIST])->data->wakeTime = wakeTime;
	TransferPCBByPriority(pcbLists[RUNNING_LIST], pcbLists[SLEEP_LIST]);	
}

void SemaphoreWaitISR(TrapFramePtr frame)
{
	int semID;
	semID = frame->eax;
	
	semaphores[semID]->value -= 1;
	if (semaphores[semID]->value < 0)
		TransferPCB(GetRunningPID(), pcbLists[RUNNING_LIST], semaphores[semID]->queue);
}

void SemaphorePostISR(TrapFramePtr frame)
{
	int semID;
	semID = frame->eax;
	semaphores[semID]->value += 1;
	if (semaphores[semID]->value <= 0 && !IsEmpty(semaphores[semID]->queue))	
	{
		TransferHeadPCB(semaphores[semID]->queue, pcbLists[READY_LIST]);
		TransferHeadPCB(pcbLists[RUNNING_LIST], pcbLists[READY_LIST]);
	}
}

void SpawnISR(TrapFramePtr frame)
{
	int address;
	int IE1;
	int IE2;
	int IE3;
	int IE4;
	
	address = frame->eax;
	IE1 = frame->edi;
	IE2 = frame->esi;
	IE3 = frame->ebx;
	IE4 = frame->ecx;

	CreateProcess(pcbLists[READY_LIST], (int (*)(void)) address, IE1, IE2, IE3, IE4);
}

void TimerISR(){

  ELAPSED_TICKS++;
  if (cons_kbhit())
    {
        char key = cons_getchar();
        switch (key)
        {
        case 't':
            TimesliceHandler();
            break;
       /* case 'z':
            SleepHandler();
            break;
        case 'a':
            AwakenHandler();
            break;
        case 'w':
            SBlockHandler();
            break; */
        case 's':
            //SUnblockHandler();
	    DisplaySemaphores();
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


void DisplaySemaphores()
{
	int i;
	for (i = 0; i < MAX_SEMAPHORES; i++)
	{
		if (semaphores[i] != NULL)
		{
			printf("Semaphore ID: %d\n", semaphores[i]->id);
			printf("Semaphore Value: %d\n", semaphores[i]->value);
			printf("Semaphore Blocked Queue: ");
			DisplayPCBList(semaphores[i]->queue);
			printf("\n\n");
		}
	}
}

void ServiceInterrupt(TrapFramePtr frame)
{
    int trapnum;
    pcbLists[RUNNING_LIST]->head->next->data->trapFrame = frame;
    trapnum = frame->trapno;
    // printf("int %d", trapnum);
    switch (trapnum)
    {
    case 0x20:
        TimerISR();
        break;
    case 0x30:
	GetPIDISR(frame);
	break;
    case 0x31:
	SleepISR(frame);
	break;
    case 0x32:
	SemaphoreWaitISR(frame);
    	break;
    case 0x33:
	SemaphorePostISR(frame);
	break;
    case 0x36:
	SpawnISR(frame);
	break;
    default:
        printf("Unhandled exception %d!", trapnum);
        exit(1);

    }
    //printf("d");
    IRQAck(trapnum-0x20);
    Dispatcher();
}


