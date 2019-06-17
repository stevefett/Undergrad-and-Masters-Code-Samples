#include <spede/stdio.h>
#include <spede/stdlib.h>
#include "list.h"
#include "kerneldata.h"

PCBNodePtr Remove(int findPid, PCBListPtr myList)
{
    PCBNodePtr walk = myList->head->next;
    bool removed = FALSE;
    
    while(walk != NULL && !removed){
        if(walk->data->pid == findPid){
            (walk->prev)->next = walk->next;
            if(walk->next != NULL){
                (walk->next)->prev = walk->prev;
            }
            else{
                myList->tail = walk->prev;
            }
            walk->next = NULL;
            walk->prev = NULL;
            removed = TRUE;
        }
        else{
            walk = walk->next;
        }
    }
    return walk;
}

int InsertByPriority(PCBNodePtr myData, PCBListPtr myList)
{    
    PCBNodePtr walk = myList->head->next;
    int targetPriority = myData->data->priority;
    bool inserted = FALSE;
    
    while(walk != NULL && !inserted){
        if(targetPriority < walk->data->priority){
            (walk->prev)->next = myData;
            myData->prev = walk->prev;
            myData->next = walk;
            walk->prev = myData;
            inserted = TRUE;
        }
        else{
            walk = walk->next;
        }
    }
    
    if(!inserted){
        Append(myData, myList);
    }
    
    return 1;
}

bool ListEmpty(PCBList *myList)
{
	return myList->head == myList->tail ? TRUE : FALSE;
}

PCBNodePtr RemoveHead(PCBListPtr myList)
{
    PCBNodePtr nodeToRemove = myList->head->next;
    
    if(nodeToRemove != NULL){
        myList->head->next = nodeToRemove->next;
        if(nodeToRemove->next == NULL){
            myList->tail = myList->head;
        }
        else{
            (nodeToRemove->next)->prev = myList->head;
        }
        nodeToRemove->next = NULL;
        nodeToRemove->prev = NULL;
    }
    return nodeToRemove;
}

int PrintList(PCBListPtr myList){

	PCBNodePtr printPtr;
	printPtr = myList->head->next;
	while (printPtr != NULL)
	{
		printf("%d ", printPtr->data->pid);
		printPtr = printPtr->next;
	}
	printf("\n");
	return 1;
}

int PrintActiveList(PCBListPtr activeList){

  PCBNodePtr printPtr;
  printPtr = activeList->head->active;
  while(printPtr != NULL){
    printf("%d ", printPtr->data->pid);
    printPtr = printPtr->active;
  }
  printf("\n");
  return 1;
}

int Initialize(PCBListPtr *newList)
{
    PCBNodePtr sentinelNode = (PCBNodePtr) malloc(sizeof(PCBNode));
	sentinelNode->next = NULL;
	sentinelNode->active = NULL;
	sentinelNode->prev = NULL;
	sentinelNode->data = NULL;
    
	*newList = (PCBList *) malloc(sizeof(PCBList));
    (*newList)->head = sentinelNode;
    (*newList)->tail = sentinelNode;
	return 1;
}

PCBNodePtr AddToActive(PCBDataPtr newData, PCBListPtr activeList)
{
	PCBNodePtr newNode = (PCBNodePtr) malloc(sizeof(PCBNode));
	newNode->next = NULL;
	newNode->prev = NULL;
	newNode->data = newData;
    
    newNode->active = activeList->head->active;
    activeList->head->active = newNode;
	return newNode;
}
	
int Append(PCBNodePtr newData, PCBListPtr myList)
{
    newData->next = NULL;
    newData->prev = myList->tail;
    myList->tail->next = newData;
    myList->tail = newData;
    
    return 1;
}

/*
int main()
{
	//PCBList *activeList = (PCBList*)malloc(sizeof(PCBList));
	//PCBList *stateList = (PCBList*)malloc(sizeof(PCBList));
	Initialize(activeList);
	Initialize(stateList);
	PCBData *blah = (PCB*)malloc(sizeof(PCB));
	blah->pid = 123;
	blah->priority = 1;
	PCBData *moo = (PCB*)malloc(sizeof(PCB));
	moo->pid = 321;
	moo->priority = 10;
	//AddToActive(blah, activeList;
	Append(AddToActive(blah, activeList), stateList);	
	Append(AddToActive(moo, activeList), stateList);
	PrintList(stateList);
	PCBList *bah = RemoveHead(stateList);
	printf("removing %d \n", bah->data->pid);
	PrintList(stateList);
//	bah = RemoveHead(stateList);
	bah->data->priority = 20;
	printf("Adding %d to list with prio = 20\n", bah->data->pid);
	InsertByPriority(bah, stateList);
	PrintList(stateList);
	bah = RemoveHead(stateList);
	printf("removing %d \n", bah->data->pid);
	PrintList(stateList);
	printf("List empty = %d \n", ListEmpty(stateList));
	printf("Removing PID# 555 \n");
	Remove(555, stateList);
	printf("Removing 123\n");
	Remove(123, stateList);
	PrintList(stateList);
	printf("List empty = %d \n", ListEmpty(stateList));
}

*/
