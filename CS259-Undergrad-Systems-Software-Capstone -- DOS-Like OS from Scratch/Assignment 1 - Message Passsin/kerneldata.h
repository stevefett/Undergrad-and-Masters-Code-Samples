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

#define MAX_SEMAPHORES 10
#define MAX_MAILBOXES 10
#define MAX_BUFFERS 10
#define BUFFER_SIZE 256


#define KERNEL_STACK_SIZE 4096
#define PROCESS_STACK_SIZE 4000
#define EFLAGS_USER_PROCESS_VALUE 0x202

#define TIMER_IRQ 0x0

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

typedef TrapFrame* TrapFramePtr;

typedef struct _PCB
{
    int pid;
    int wakeTime;
    TrapFramePtr trapFrame;
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

typedef struct _Semaphore
{
    int id;
    int value;
    PCBList* queue;
} Semaphore;

typedef Semaphore* SemaphorePtr;

typedef short bool;
#define TRUE 1
#define FALSE 0

extern PCBListPtr pcbLists[];
extern SemaphorePtr semaphores[];
extern unsigned char globalBuffers[][1024];
extern bool DONE;

extern unsigned int ELAPSED_TICKS;

extern int ConsoleScreenAvailSemaphore;
extern int FreeBufferMailboxID;
extern int DirectedMailBoxID;

PCBDataPtr AllocatePCBData(void);
int GetRunningPID(void);
PCBNodePtr GetHead(PCBListPtr);
int GetHeadPID(PCBListPtr);
int GetHeadPriority(PCBListPtr);
int CreateStaticProcess(PCBListPtr, int(*)(void));
int CreateProcess(PCBListPtr, int(*)(void), int, int, int, int);
int TransferHeadPCB(PCBListPtr, PCBListPtr);
int TransferPCB(int, PCBListPtr, PCBListPtr);
int TransferPCBByPID(int, PCBListPtr, PCBListPtr);
int TransferPCBByPriority(PCBListPtr, PCBListPtr);
int DisplayPCBList(PCBListPtr);
bool IsEmpty(PCBListPtr);
int CreatePCBLists(void);
int CreateSemaphoreBlockedList(PCBListPtr *);

void Dispatcher(void);

void InterruptHandler(void);
void IRQAck(unsigned);
void IRQEnable(unsigned);

#endif
