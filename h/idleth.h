//File: idleth.h
#ifndef _idleth_h_
#define _idleth_h_

#include "thread.h"

class Thread;

class IdleThread:public Thread{
public:
	IdleThread();
	void start();
	virtual void run();
};


#endif