//File: thread.cpp

#include "thread.h"
#include "pcb.h"
#include "schedule.h"
#include "timer.h"
#include <iostream.h>
#include <stdio.h>

Thread::Thread(StackSize stackSize, Time timeSlice){
	lock();
	myPCB=new PCB(stackSize, timeSlice, this);
	unlock();
}

Thread::~Thread(){
	lock();
	waitToComplete();
	delete myPCB;
	unlock();
}

void Thread::start(){
	lock();
	myPCB->myStatus=READY;
	myPCB->createStack();
	Scheduler::put(myPCB);
	unlock();
}

void Thread::waitToComplete(){ //ne cekamo ako su sledeca stanja
	lock();
	if(myPCB->myStatus==TERMINATED || myPCB->myStatus==NEW || myPCB==(PCB*)Timer::running || this==Timer::idle || this==Timer::starting){
		unlock();
		return;
	}
	Timer::running->myStatus=BLOCKED;
	myPCB->myWaitQueue->put(Timer::running);
	dispatch();
	unlock();
}



void dispatch(){
	lock();
	Timer::eksplicitno=1;
	Timer::timerInt();
	Timer::eksplicitno=0;
	unlock();
}
