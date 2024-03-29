#include <spede/stdio.h>
#include <spede/stdlib.h>
#include <spede/flames.h>
#include <spede/ctype.h>
#include <spede/machine/seg.h>
#include <spede/machine/proc_reg.h>
#include <spede/machine/io.h>
#include <spede/util.h>
#include "kerneldata.h"
#include "EnterProcess.h"
#include "idle.h"
#include "init.h"
#include "producerconsumer.h"
#include "mailbox.h"

unsigned int ELAPSED_TICKS = 0;
int ConsoleScreenAvailSemaphore = 6;
int FreeBufferMailboxID = 7;
int DirectedMailBoxID = 0;
PCBListPtr pcbLists[NUM_OF_PCB_LISTS];
bool DONE = FALSE;
unsigned char globalBuffers[MAX_BUFFERS][1024];
int i;

char Kernel_Stack[KERNEL_STACK_SIZE];
MailBoxPtr mailBoxes[MAX_MAILBOXES];

SemaphorePtr semaphores[MAX_SEMAPHORES];

char boundedBuffer[2][10];

int initialDelayValues[12];

typedef void (*PFV)(void);

extern void TimerISREntry(void);
extern void GetPIDEntry(void);
extern void SleepEntry(void);
extern void SemaphoreWaitEntry(void);
extern void SemaphorePostEntry(void);
extern void SendMessageEntry(void);
extern void ReceiveMessageEntry(void);
extern void SpawnEntry(void);

void SetExceptionHandler(int exception, PFV handler, struct i386_gate * idt_table){
    
    struct i386_gate * vectorAddr = &idt_table[exception];
    
    fill_gate(vectorAddr, PTR2INT(handler), get_cs(), 0xE, 0);
}

void InitializeInterrupts(){
    
    struct i386_gate * idt_table;
    struct pseudo_descriptor where_idt;
    
    // __asm__ ( "leal %0,%%eax \n" 
    // "sidt \(%%eax\)" 
    // : "=m" (where_idt.limit) : : "eax" );
    
    __asm__ ( "leal %0,%%eax \n" 
    "sidt (%%eax)" 
    : "=m" (where_idt.limit) : : "eax" );
    
    idt_table = (struct i386_gate *) where_idt.linear_base;
    SetExceptionHandler(0x20, TimerISREntry, idt_table);
    SetExceptionHandler(0x30, GetPIDEntry, idt_table);
    SetExceptionHandler(0x31, SleepEntry, idt_table);
    SetExceptionHandler(0x32, SemaphoreWaitEntry, idt_table);
    SetExceptionHandler(0x33, SemaphorePostEntry, idt_table);
    SetExceptionHandler(0x34, SendMessageEntry, idt_table);
    SetExceptionHandler(0x35, ReceiveMessageEntry, idt_table);
    SetExceptionHandler(0x36, SpawnEntry, idt_table);
    outportb(0x21, ~0x01);
    outportb(0xA1, ~0);
}

void ReadDelayValues(){
    int i;
    for(i = 0; i < 4; i++){
        int num;
        cons_printf("\nFlicker %d ON time (sec): ", i+1);
        initialDelayValues[i*2] = 0;
        while(isdigit(num = cons_getchar())){
            initialDelayValues[i*2] = initialDelayValues[i*2]*10 + (num- '0');
        }
        cons_printf("\nFlicker %d OFF time (sec): ", i+1);
        initialDelayValues[(i*2)+1] = 0;
        while(isdigit(num = cons_getchar())){
            initialDelayValues[(i*2)+1] = initialDelayValues[(i*2)+1]*10 + (num-'0');
        }
    }
    for(i = 0; i < 2; i++){
        int num;
        cons_printf("\nProducer %d DELAY time (sec): ", i+1);
        initialDelayValues[(i*2)+8] = 0;
        while(isdigit(num = cons_getchar())){
            initialDelayValues[(i*2)+8] = initialDelayValues[(i*2)+8]*10 + (num-'0');
        }
        cons_printf("\nConsumer %d DELAY time (sec): ", i+1);
        initialDelayValues[(i*2)+9] = 0;
        while(isdigit(num = cons_getchar())){
            initialDelayValues[(i*2)+9] = initialDelayValues[(i*2)+9]*10 + (num-'0');
        }
    }
}

void InitializeFlickerSemaphores(){
    int i;
    for(i = 0; i < 2; i++){
        semaphores[i]->id = i;
        semaphores[i]->value = 1;
        CreateSemaphoreBlockedList(&(semaphores[i]->queue));
    }
}

void InitializeBoundedBufferSemaphores(){
    int k;
    for(k = 2; k < 6; k++){
        semaphores[k]->id = k;
        semaphores[k]->value = 10;
        CreateSemaphoreBlockedList(&(semaphores[k]->queue));
        k++;
        semaphores[k]->id = k;
        semaphores[k]->value = 0;
        CreateSemaphoreBlockedList(&(semaphores[k]->queue));
    }
}

void InitializeIPCSemaphores()
{
	int k;
	for (k = 6; k < MAX_SEMAPHORES; k++)
	{
		semaphores[k]->id = k;
        	semaphores[k]->value = 1;	
	}
	
}

void InitializeSemaphores(){
  int i;
  for(i = 0; i < MAX_SEMAPHORES; i++){
    semaphores[i] = (SemaphorePtr) malloc(sizeof(Semaphore));
  }
    InitializeFlickerSemaphores();
    InitializeBoundedBufferSemaphores();
}

void InitializeBuffers()
{
	int i;
	unsigned char* buffer;
	for(i = 0; i < MAX_SEMAPHORES; i++)
	{
		buffer = (unsigned char*)malloc(sizeof(BUFFER_SIZE));
		globalBuffers[i][0] = buffer;
	}
}

void InitializeMailBoxes()
{
	int i;
	for (i = 0; i < MAX_MAILBOXES; i++)
	{
		if (i == 0)
			MailBoxCreate(i, DIRECTED);
		else
			MailBoxCreate(i, UNDIRECTED);
	}	
	
}

void InitOS(){

    InitializeInterrupts();

    CreatePCBLists();

    ReadDelayValues();
    
    InitializeSemaphores();
    
    InitializeBuffers();
    InitializeMailBoxes();

    CreateStaticProcess(pcbLists[IDLE_LIST], idle);
    CreateStaticProcess(pcbLists[READY_LIST], init);
    
    // CreateProcess(pcbLists[READY_LIST], &flicker1);
	// CreateProcess(pcbLists[READY_LIST], &flicker2);
    // CreateProcess(pcbLists[READY_LIST], &flicker3);
    // CreateProcess(pcbLists[READY_LIST], &flicker4);
    // CreateProcess(pcbLists[READY_LIST], &flicker5);
    // CreateProcess(pcbLists[READY_LIST], &flicker6);
    // CreateProcess(pcbLists[READY_LIST], &flicker7);
    // CreateProcess(pcbLists[READY_LIST], &flicker8);
		
}

void Dispatcher(){
    
	TrapFrame *tf;
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
    
    tf = pcbLists[RUNNING_LIST]->head->next->data->trapFrame;
	IRQEnable(TIMER_IRQ);
	EnterProcess (tf);
}

int main(){

    InitOS();
    Dispatcher();
    
    return 0;
}
