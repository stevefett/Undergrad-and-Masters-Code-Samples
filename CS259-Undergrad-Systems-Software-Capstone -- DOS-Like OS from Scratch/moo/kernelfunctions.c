#include <spede/stdlib.h>
#include <spede/stdio.h>
#include "kerneldata.h"
#include "list.h"

int pidCounter = 0;

PCBDataPtr AllocatePCBData(){

    return (PCBDataPtr) malloc(sizeof(PCBData));
}

int CreateProcess(PCBListPtr initialStateList){

    PCBDataPtr newProcess;
    newProcess = AllocatePCBData();
    newProcess->pid = pidCounter++;
    newProcess->priority = newProcess->pid;
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
