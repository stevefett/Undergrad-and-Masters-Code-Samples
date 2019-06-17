#include <spede/machine/asmacros.h>
#define KERNEL_DATASEG 0x10
#define KERNEL_STACK_SIZE 0x20

ENTRY(timer_ISR_Entry)
	pushl $0
	pushl $0x20
	jmp common_ISR

	common_ISR:

		pusha
		pushl %ds
		pushl %es
		pushl %fs
		pushl %gs

		movl %esp,%ecx

		cld

		movw $(KERNEL_DATASEG),%ax
		mov %ax,%ds
		mov %ax,%es

		leal CNAME(Kernel_Stack)+KERNEL_STACK_SIZE,%esp
		pushl %ecx

		call CNAME(ServiceInterrupt)

