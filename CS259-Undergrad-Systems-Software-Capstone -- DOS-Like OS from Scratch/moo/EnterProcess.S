#include <spede/machine/asmacros.h>

ENTRY(EnterProcess)
	movl 4(%esp),%eax

	movl %eax,%esp

	popl %gs
	popl %fs
	popl %es
	popl %ds

	popa

	add $8,%esp
	iret

