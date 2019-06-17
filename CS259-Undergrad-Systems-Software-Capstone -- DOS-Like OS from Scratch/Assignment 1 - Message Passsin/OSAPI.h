/**  File: OSAPI.h
 * This file defines the Application Programming Interface (API)
 * for the OS Kernel; that is, the set of all Kernel Service functions
 * that can be invoked by a process running in the OS.
 * Each API service is implemented as a C macro which defines a set
 * of assembly-language statements invoking the corresponding service.
 * For the Intel architecture, each service is invoked by an "int"
 * instruction with the appropriate input and result (output) values
 * stored in registers.
 * The software interrupt values assigned to various traps are as follows:
 *
 *		GETPID    $0x30
 *		SLEEP     $0x31
 *		WAIT      $0x32
 *		SIGNAL    $0x33
 * 		SEND_MSG  $0x34
 *		RECV_MSG  $0x35
 *		SPAWN     $0x36
 */
#ifndef OS_API_H
#define OS_API_H
 
 
#ifndef _SPEDE_FLAMES_H
#include <spede/flames.h>
#endif


/** GETPID macro: requests the kernel to place the Process ID of
 *  the currently running process into the EAX register, which 
 *  the macro code then copies to the specifed macro parameter "pid".
 */
#define GETPID(pid)             \
    ASM(" int $0x30"            \
        : "=a"(pid) );          //store returned EAX in pid after trap


/** SLEEP macro: requests the kernel to put the currently running
 *  process to sleep for the number of seconds specified by the 
 *  input parameter, which the macro passes to the kernel in EAX.
 */
#define SLEEP(seconds)          \
    ASM(" int $0x31"            \
        : /*no outputs*/        \
        : "a"(seconds) );       //fetch value of seconds to EAX before trap


/** WAIT macro: requests the kernel to cause the currently running
 *  process to execute a WAIT operation on the specified semaphore.
 *  The macro passes the semaphore ID to the kernel in EAX.
 */
#define WAIT(semaphoreID)       \
    ASM(" int $0x32"            \
        : /* no outputs */      \
        : "a"(semaphoreID) );   //fetch semaphoreID to EAX before trap


/** SIGNAL macro:  requests the kernel to cause the currently running
 *  process to execute a SIGNAL operation on the specified semaphore.
 *  The macro passes the semaphore ID to the kernel in EAX.
 */
#define SIGNAL(semaphoreID)     \
    ASM(" int $0x33"            \
        : /* no outputs */      \
        : "a"(semaphoreID) );   //fetch semaphoreID to EAX before trap

/** SEND macro:  requests the kernel to perform a Send_Message operation
 *  on behalf of the currently running process.
 *	The mailbox ID is passed to the kernel in the upper half (16 bits) of
 *  EAX; the PID of the intended receiver is passed to the kernel in the
 *  lower half of EAX; the message to be sent consists of six longwords
 *  stored in registers as follows:
 *  		EDI, ESI contain Message Words 1 and 2;
 *  		EBX, ECX, and EDX contain Message Words 3, 4, and 5;
 *			EBP contains Message Word 6.
 *  The macro packs the message words into registers as described above;
 *  the kernel must unpack them as specified.
 *  On return from the macro no registers are changed (unless the kernel
 *  changed them).
 */
#define SEND(MailboxID, ReceiverID, MW1, MW2, MW3, MW4, MW5, MW6)   \
    ASM(" pushl %%ebp       \n"   /* make room on stack for MW6*/   \
        " movl  %1,%%edi    \n"   /* load MW1 */                    \
        " movl  %2,%%esi    \n"   /* load MW2 */                    \
        " movl  %6,%%ebp    \n"   /* load MW6 (others loaded by GCC)*/ \
        " int   $0x34       \n"   /* SEND trap */                   \
        " popl  %%ebp       \n"   /* restore old frame ptr */       \
        : /* no outputs */                                          \
        : "a"( ((MailboxID) << 16) | (ReceiverID) ), /*ld MB & Rcvr*/ \
          "g"(MW1), "g"(MW2), "b"(MW3),                             \
          "c"(MW4), "d"(MW5), "g"(MW6)                              \
        : "edi", "esi"  );        /* tell compiler we use these */


/** RECEIVE macro:  requests the kernel to perform a Receive_Message 
 *  operation on behalf of the currently running process.
 *  The mailbox ID is passed to the kernel in EAX.
 *  After the trap returns, the macro expects the kernel to have stored
 *  6 message words in registers EDI, ESI, EBX, ECX, EDX, and EBP respectively,
 *  and that the kernel has put the PID of the SENDER of the message into EAX.
 *  The macro copies these seven return values into the specified macro
 *	parameters.
 */
#define RECEIVE(MailboxID, SenderID, MW1, MW2, MW3, MW4, MW5, MW6)    \
    ASM(" pushl %%ebp        \n"    /* make room on stack for MW6 */  \
        " int $0x35          \n"    /* Receive trap */                \
        /* After the trap, EBP contains a message word so it can't    \
           be used for its normal local-variable addressing function. \
           Play tricks by restoring EBP into EBX then swapping.       \
         */                                                           \
        " pushl %%ebx           \n"                                   \
        " movl  %%esp,%%ebx     \n" /*get addr of saved ebp */        \
        " movl  4(%%ebx),%%ebx  \n" /*original ebp -> ebx */          \
        " xchg  %%ebx,%%ebp     \n"                                   \
        " movl  %%ebx,%6        \n" /*store MW6 */                    \
        " popl  %3              \n" /*store MW3 (from ebx)*/          \
        " addl  $4,%%esp        \n"	/*skip over orig ebp */           \
        : "=a"(SenderID), "=D"(MW1), "=S"(MW2), "=g"(MW3),            \
          "=c"(MW4), "=d"(MW5), "=g"(MW6)                             \
        : "0"(MailboxID)                                              \
        : "ebx", "edx" ) ;          /*tell compiler we use these*/


/** SPAWN macro: requests the kernel to spawn a new process as defined by
 * the specified input parameters.  The first parameter is the starting
 * address (program counter, IP) of the new process; the additional four 
 * parameters are "initial environment" values to be passed to the new 
 * process on its stack.  The macro passes the Program Counter to the kernel 
 * in EAX, and passes the four IE values in EDI, ESI, EBX, and ECX.
 */
#define SPAWN(Address, IE1, IE2, IE3, IE4)                        \
    ASM(" movl  %1,%%edi    \n"    /* load IE1 */                 \
        " movl  %2,%%esi    \n"    /* load IE2 */                 \
        " int   $0x36       \n"                                   \
        : /* no outputs */                                        \
        : "a"(Address), "g"(IE1), "g"(IE2), "b"(IE3), "c"(IE4)    \
        : "edi", "esi" );          /* tell GCC we change these*/
        
#endif