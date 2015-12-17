//File: kernelev.h
#ifndef _kernelev_h_
#define _kernelev_h_

#include "queue.h"
#include "pcb.h"
#include "event.h"

typedef unsigned char IVTNo;  //morao sam i ovde da definisem
class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	
	void wait();
	void signal();
	
	friend class IVTEntry;
private:
	int val;
	PCB* owner;
	//IVTNo entry;
	
	
};

#endif