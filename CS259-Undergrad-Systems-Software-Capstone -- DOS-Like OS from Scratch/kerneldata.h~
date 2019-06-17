#ifndef KERNEL_DATA_H
#define KERNEL_DATA_H



#define NUM_OF_PCB_LISTS 9

#define ACTIVE_LIST 0
#define READY_LIST 1
#define RUNNING_LIST 2
#define SLEEP_LIST 3
#define S1BLOCKED_LIST 4
#define S2BLOCKED_LIST 5
#define M1BLOCKED_LIST 6
#define M2BLOCKED_LIST 7
#define IDLE_LIST 8

typedef unsigned short seg_type_t;

typedef struct trap_frame{
	seg_type_t gs;
	seg_type_t _notgs;
	seg_type_t fs;
	seg_type_t _notfs;
	seg_type_t es;
	seg_type_t _notes;
	seg_type_t ds;
	seg_type_t _notds;
	
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int esp;
	unsigned int ebx;
	unsigned int edx;
	unsigned int ecx;
	unsigned int eax;

	unsigned int trapno;
	unsigned int err;
	
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;

} TrapFrame;

typedef struct _PCB
{
	int pid;
	int priority;
  TrapFrame *ProcessStackPointer;
  
} PCBData ;

typedef PCBData* PCBDataPtr;

typedef struct _PCBNode
{
	struct _PCBNode *next;
	struct _PCBNode *active;
	PCBDataPtr data;
	struct _PCBNode *prev;
} PCBNode ;

typedef PCBNode* PCBNodePtr;

typedef struct _PCBList
{
    PCBNodePtr head;
    PCBNodePtr tail;
} PCBList;

typedef PCBList* PCBListPtr;

typedef short bool;
#define TRUE 1
#define FALSE 0

extern PCBListPtr pcbLists[];
extern bool DONE;

PCBDataPtr AllocatePCBData(void);
int GetRunningPID(void);
int GetHeadPID(PCBListPtr);
int GetHeadPriority(PCBListPtr);
int CreateProcess(PCBListPtr);
int TransferHeadPCB(PCBListPtr, PCBListPtr);
int TransferPCB(int, PCBListPtr, PCBListPtr);
int TransferPCBByPID(int, PCBListPtr, PCBListPtr);
int TransferPCBByPriority(int, PCBListPtr, PCBListPtr);
int DisplayPCBList(PCBListPtr);
bool IsEmpty(PCBListPtr);
int CreatePCBLists(void);

void InterruptHandler(void);

#endif
