#include <spede/machine/asmacros.h>

#define KERNEL_DATASEG 0x10
#define KERNEL_STACK_SIZE 4096


ENTRY(TimerISREntry)
	pushl $0
	pushl $0x20
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
