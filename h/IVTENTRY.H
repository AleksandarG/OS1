//File: ivtentry.h
#ifndef _ivtentry_h_
#define _ivtentry_h_

#include "event.h"
#include "kernelev.h"
#include "pcb.h"
typedef unsigned char IVTNo;       //morao sam i ovde
typedef void interrupt (*intH)(...);
class KernelEv;

class IVTEntry{
public:
	static IVTEntry* first;
	static IVTEntry* last;
	IVTEntry* next;
	IVTEntry(IVTNo ivtNo, intH nInt);
	~IVTEntry();
	void callOldIntR();
	void signal();
	static IVTEntry* getEntry(IVTNo ivtNo);
	friend class KernelEv;
	
private:
	KernelEv* myEv;
	intH oldInt;
	IVTNo numEntry;
};

#endif