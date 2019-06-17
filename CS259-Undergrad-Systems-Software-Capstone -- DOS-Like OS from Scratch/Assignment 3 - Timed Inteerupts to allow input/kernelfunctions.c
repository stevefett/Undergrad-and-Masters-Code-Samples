#include <spede/stdlib.h>
#include <spede/stdio.h>
#include "kerneldata.h"
#include "list.h"

int pidCounter = 0;

short GetCS(){

    short csValue;
    __asm__ ("movw %%cs, %0" : "=r" (csValue));
    return csValue;
}

short GetDS(){

    short dsValue;
    __asm__ ("movw %%ds, %0" : "=r" (dsValue));
    return dsValue;
}

short GetES(){

    short esValue;
    __asm__ ("movw %%es, %0" : "=r" (esValue));
    return esValue;
}

short GetFS(){

    short fsValue;
    __asm__ ("movw %%fs, %0" : "=r" (fsValue));
    return fsValue;
}

short GetGS(){

    short gsValue;
    __asm__ ("movw %%gs, %0" : "=r" (gsValue));
    return gsValue;
}

PCBDataPtr AllocatePCBData(){

    return (PCBDataPtr) malloc(sizeof(PCBDataPtr));
}


int CreateStaticProcess(PCBListPtr initialStateList, int (*entryPoint)(void)){

    PCBDataPtr newProcess;
    newProcess = AllocatePCBData();
    newProcess->pid = pidCounter++;
    newProcess->trapFrame = ((TrapFrame*)malloc(PROCESS_STACK_SIZE))+PROCESS_STACK_SIZE-sizeof(TrapFrame);
    newProcess->wakeTime = 0;
    newProcess->trapFrame->eip = (unsigned int)entryPoint;
    newProcess->trapFrame->cs = GetCS();
    newProcess->trapFrame->eflags = EFLAGS_USER_PROCESS_VALUE;
    newProcess->trapFrame->esp = (unsigned int)newProcess->trapFrame;
    newProcess->trapFrame->gs = GetGS();
    newProcess->trapFrame->fs = GetFS();
    newProcess->trapFrame->es = GetES();
    newProcess->trapFrame->ds = GetDS();
    newProcess->trapFrame->edi = 0x05;    
    newProcess->trapFrame->esi = 0x06;
    newProcess->trapFrame->ebp = 0x07;
    newProcess->trapFrame->ebx = 0x08;
    newProcess->trapFrame->edx = 0x09;
    newProcess->trapFrame->ecx = 0x0a;
    newProcess->trapFrame->eax = 0x0b;
    newProcess->trapFrame->trapno = 0x0c;
    newProcess->trapFrame->err = 0x0d;

    return Append(AddToActive(newProcess, pcbLists[ACTIVE_LIST]), initialStateList);
}


int CreateProcess(PCBListPtr initialStateList, int (*entryPoint)(void), int IE1, int IE2, int IE3, int IE4)
{
    int* IEPtr;
    int *StackPtr;
    PCBDataPtr newProcess;
    newProcess = AllocatePCBData();
    newProcess->pid = pidCounter++;
    //newProcess->trapFrame = ((TrapFrame*)malloc(PROCESS_STACK_SIZE))+PROCESS_STACK_SIZE-sizeof(TrapFrame) - (5 * sizeof(int));
    StackPtr = (int *) (malloc(PROCESS_STACK_SIZE) + PROCESS_STACK_SIZE);
    --StackPtr;
    *StackPtr = IE4;
    --StackPtr;
    *StackPtr = IE3;
    --StackPtr;
    *StackPtr = IE2;
    --StackPtr;
    *StackPtr = IE1;
    --StackPtr;
    *StackPtr = 0L;
    newProcess->trapFrame = (TrapFrame *) ((void *) StackPtr - sizeof(TrapFrame));
    //IEPtr = (int *)(newProcess->trapFrame + sizeof(TrapFrame));
    //IEPtr++;
    //*IEPtr = IE1;
    //IEPtr++;
    //*IEPtr = IE2;
    //IEPtr++;
    //*IEPtr = IE3;
    //IEPtr++;
    //*IEPtr = IE4;
    newProcess->wakeTime = 0;
    newProcess->trapFrame->eip = (unsigned int)entryPoint;
    newProcess->trapFrame->cs = GetCS();
    newProcess->trapFrame->eflags = EFLAGS_USER_PROCESS_VALUE;
    newProcess->trapFrame->esp = (unsigned int)newProcess->trapFrame;
    newProcess->trapFrame->gs = GetGS();
    newProcess->trapFrame->fs = GetFS();
    newProcess->trapFrame->es = GetES();
    newProcess->trapFrame->ds = GetDS();
    newProcess->trapFrame->edi = 0x05;    
    newProcess->trapFrame->esi = 0x06;
    newProcess->trapFrame->ebp = 0x07;
    newProcess->trapFrame->ebx = 0x08;
    newProcess->trapFrame->edx = 0x09;
    newProcess->trapFrame->ecx = 0x0a;
    newProcess->trapFrame->eax = 0x0b;
    newProcess->trapFrame->trapno = 0x0c;
    newProcess->trapFrame->err = 0x0d;
    return Append(AddToActive(newProcess, pcbLists[ACTIVE_LIST]), initialStateList);
}


int TransferPCB(int pid, PCBListPtr sourceList, PCBListPtr destList){

    return Append(Remove(pid, sourceList), destList);
}

int TransferHeadPCB(PCBListPtr sourceList, PCBListPtr destList){

    return Append(RemoveHead(sourceList), destList);
}

int TransferPCBByPriority(PCBListPtr sourceList, PCBListPtr destList){
    //Works because pid = priority. If that changes, then need another remove function.
    return InsertByPriority(RemoveHead(sourceList), destList);
}

int TransferPCBByPID(int pid, PCBListPtr sourceList, PCBListPtr destList){
    
    PCBNodePtr temp = Remove(pid, sourceList);
    return temp == NULL ? -1 : Append(temp, destList);
}

int GetRunningPID(){

    return GetHeadPID(pcbLists[RUNNING_LIST]);
}

PCBNodePtr GetHead(PCBListPtr pcbList){
    return pcbList->head->next;
}

int GetHeadPID(PCBListPtr pcbList){
    
    return pcbList->head->next != NULL ? pcbList->head->next->data->pid : -1;
}

int GetHeadPriority(PCBListPtr pcbList){
    
    return pcbList->head->next != NULL ? pcbList->head->next->data->wakeTime : -1;
}

int DisplayPCBList(PCBListPtr pcbList){
    
    return pcbList == pcbLists[ACTIVE_LIST] ? PrintActiveList(pcbList) : PrintList(pcbList);
}

bool IsEmpty(PCBListPtr pcbList){
    
    return ListEmpty(pcbList);
}

int CreatePCBLists(){

    int i;
    for(i = 0; i < NUM_OF_PCB_LISTS; i++){
        Initialize(&(pcbLists[i]));
    }
    return 1;
}

int CreateSemaphoreBlockedList(PCBListPtr* list){
    Initialize(list);
    return 1;   
}
