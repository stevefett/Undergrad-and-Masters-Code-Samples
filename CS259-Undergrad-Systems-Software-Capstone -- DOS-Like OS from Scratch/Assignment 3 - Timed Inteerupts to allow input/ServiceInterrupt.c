#include "trap.h"

void ServiceInterrupt(trap_fram *oldSP)
{
	RunningPCB->SystemStackPointer = oldSP;
	trapNum = oldSP->trapno;
	
	case (trapNum) of
		Timer: ServiceTimerInterrupt();
	default: printf("Unhandled interrupt %d", trapNum);
		exit(1);
	end case;

	DispatchAProcess();
}

