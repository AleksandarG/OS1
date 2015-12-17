//File: pcb.h

#ifndef _pcb_h_
#define _pcb_h_

#include <dos.h>
#include "schedule.h"
#include "thread.h"
#include "queue.h"
#include "idleth.h"
#include "kernelev.h"



#define lock(){ asm{ pushf; cli;}}
#define unlock(){ asm{ popf}}
class Queue;
class KernelEv;

enum Status {NEW, READY, BLOCKED, TERMINATED };


 
class PCB{
public:
	PCB(StackSize stackSize, Time timeSlice, Thread *t);
	~PCB();
	
	static void wrapper();
	
	void createStack();
	/* prebaceno u timer.h, ovde pravilo probleme
	static Thread* starting;
	static IdleThread* idle;
	static PCB* running;
*/
protected:
	friend class Thread;
	friend class Timer;
	friend void dispatch();
	friend class IdleThread;
	friend class KernelSem;
	friend class KernelEv;
	
private:
	unsigned *myStack;
	StackSize myStackSize;
	Thread *myThread;
	unsigned int sp, ss;
	Status myStatus;
	Time myTimeSlice;
	volatile Time myTimePassed;
	Queue *myWaitQueue;
	KernelEv* myBlockedEv;
};

#endif