void DispatchAProcess()
{
	SelectProcess();
	StartRunningProcess();
}

void SelectProcess()
{
	/* code to choose the next process to be run and make "RunningPCB" (head of running list) point to that process's PCB */

}

void StartRunningProcess()
{
	EnableTimerInterrupt();

	/* get runningPCB's stack pointer, which we assume points to the beginning of a "trap frame" on the top of the process's stack.  */
	newSP = RunningPCB->SystemStackPointer;

	/* invoke assembly code which uses newSP to pop the process's registers off the stack (out of the trap frame and into the CPU) then uses IRET to transfer to the new process. */
	EnterProcess(newSP);
}

