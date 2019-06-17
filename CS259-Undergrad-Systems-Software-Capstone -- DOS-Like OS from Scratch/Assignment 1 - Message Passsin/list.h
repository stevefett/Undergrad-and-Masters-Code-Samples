/* List Routine Control Header -- list.h
	v0.1
*/

#ifndef LIST_H
#define LIST_H

#include "kerneldata.h"

//Sets the next, curr, and prev ptrs as NULL when the list is fresh.	
int Initialize (PCBListPtr *pcbList);

//Adds a PCB pointer to the start of the Active List and returns created 
//node
PCBNodePtr AddToActive (PCBDataPtr newNode, PCBListPtr activeList);

//Appends a PCBList pointer to the end of a specified PCB state list
int Append (PCBNodePtr newData, PCBListPtr myList);

//Removes the PCB at the head of the indicated list, returning a ptr.
//Returns NULL if list was empty.
PCBNodePtr RemoveHead (PCBListPtr myList);

//Checks to see if the list is empty.
bool ListEmpty(PCBListPtr myList);

//Inserts a PCB into a list by priority, lowest first.  
//Currently based on PID #
int InsertByPriority (PCBNodePtr insertMe, PCBListPtr myList);

//Removes a PCB based on requested PID # and returns a ptr to that PCB.
PCBNodePtr Remove (int pid, PCBListPtr myList);

//Walks the list printing the PID of each process in it.
int PrintList (PCBListPtr myList);

//Walks the active list, printing the PID of each process in it.
int PrintActiveList (PCBListPtr myList);

#endif
