//File: timer.h
#ifndef _timer_h_
#define _timer_h_

#include "thread.h"
#include "pcb.h"
#include "idleth.h"

typedef void interrupt (*pInterrupt)();

class Timer{
public:

	static void inic();
	static void restore();
	static volatile int eksplicitno;
	static void interrupt timerInt(...);
	static void interrupt (*oldRoutine)(...);

	static Thread* starting;
	static IdleThread* idle;
	static PCB* running;
	friend class KernelSem;
	friend class Thread;
	friend class PCB;
};

#endif