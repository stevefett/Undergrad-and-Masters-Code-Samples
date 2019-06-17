#include <spede/machine/asmacros.h>

#define KERNEL_DATASEG 0x10
#define KERNEL_STACK_SIZE 4096


ENTRY(TimerISREntry)
	pushl $0
	pushl $0x20
	jmp CommonISR

ENTRY(GetPIDEntry)
	pushl $0
	pushl $0x30
	jmp CommonISR

ENTRY(SleepEntry)
	pushl $0
	pushl $0x31
	jmp CommonISR

ENTRY(SemaphoreWaitEntry)
	pushl $0
	pushl $0x32
	jmp CommonISR

ENTRY(SemaphorePostEntry)
	pushl $0
	pushl $0x33
	jmp CommonISR

ENTRY(SpawnEntry)
	pushl $0
	pushl $0x36
	jmp CommonISR

CommonISR:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs

	movl %esp, %ecx
	cld
	movw $(KERNEL_DATASEG), %ax
	mov %ax, %ds
	mov %ax, %es
	
	leal CNAME(Kernel_Stack) + KERNEL_STACK_SIZE, %esp

	pushl %ecx

	call CNAME(ServiceInterrupt)
