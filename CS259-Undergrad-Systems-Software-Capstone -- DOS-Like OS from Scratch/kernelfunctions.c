#include <spede/stdlib.h>
#include <spede/stdio.h>
#include "kerneldata.h"
#include "list.h"

int pidCounter = 0;

PCBDataPtr AllocatePCBData(){

    return (PCBDataPtr) malloc(sizeof(PCBDataPtr));
}

int CreateProcess(PCBListPtr initialStateList, int (*entryPoint)(void)){

    PCBDataPtr newProcess;
    newProcess = AllocatePCBData();
    newProcess->pid = pidCounter++;
    newProcess->TrapFramePtr = ((TrapFrame*)malloc(4000))+4000-sizeof(TrapFrame);
    newProcess->priority = newProcess->pid;
    newProcess->TrapFramePtr->eip = (unsigned int)entryPoint;
    newProcess->TrapFramePtr->eflags = 0x202;
    newProcess->TrapFramePtr->esp = (unsigned int)newProcess->TrapFramePtr;
    newProcess->TrapFramePtr->gs = 0x01;
    newProcess->TrapFramePtr->fs = 0x02;
    newProcess->TrapFramePtr->es = 0x03;
    newProcess->TrapFramePtr->ds = 0x04;
    newProcess->TrapFramePtr->edi = 0x05;    
    newProcess->TrapFramePtr->esi = 0x06;
    newProcess->TrapFramePtr->ebp = 0x07;
     newProcess->TrapFramePtr->ebx = 0x08;
    newProcess->TrapFramePtr->edx = 0x09;
    newProcess->TrapFramePtr->ecx = 0x0a;
    newProcess->TrapFramePtr->eax = 0x0b;
    newProcess->TrapFramePtr->trapno = 0x0c;
    newProcess->TrapFramePtr->err = 0x0d;
 


    return Append(AddToActive(newProcess, pcbLists[ACTIVE_LIST]), initialStateList);
}

int TransferPCB(int pid, PCBListPtr sourceList, PCBListPtr destList){

    return Append(Remove(pid, sourceList), destList);
}

int TransferHeadPCB(PCBListPtr sourceList, PCBListPtr destList){

    return Append(RemoveHead(sourceList), destList);
}

int TransferPCBByPriority(int priority, PCBListPtr sourceList, PCBListPtr destList){
    //Works because pid = priority. If that changes, then need another remove function.
    return InsertByPriority(Remove(priority, sourceList), destList);
}

int TransferPCBByPID(int pid, PCBListPtr sourceList, PCBListPtr destList){
    
    PCBNodePtr temp = Remove(pid, sourceList);
    return temp == NULL ? -1 : Append(temp, destList);
}

int GetRunningPID(){

    return GetHeadPID(pcbLists[RUNNING_LIST]);
}

int GetHeadPID(PCBListPtr pcbList){
    
    return pcbList->head->next != NULL ? pcbList->head->next->data->pid : -1;
}

int GetHeadPriority(PCBListPtr pcbList){
    
    return pcbList->head->next != NULL ? pcbList->head->next->data->priority : -1;
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
