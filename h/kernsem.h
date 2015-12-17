//File: kernsem.h
#ifndef _kernsem_h_
#define _kernsem_h_

#include "queue.h"
#include "pcb.h"
#include "timer.h"

class KernelSem{
public:
	KernelSem(int initValue=1);
	~KernelSem();
	void wait();
	void signal();
	
	int value() const{return val;}
	
protected:
	void block();
	void deblock();
	
private:
	int val;
	Queue* blockedSem;
};

#endif