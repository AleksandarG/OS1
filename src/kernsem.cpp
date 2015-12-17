//File: kernsem.cpp
#include "kernsem.h"

KernelSem::KernelSem(int initValue){
	val=initValue;
	blockedSem=new Queue();
}

KernelSem::~KernelSem(){
	delete blockedSem;
}

void KernelSem::wait(){
	if(--val<0){
		block();
	}
}

void KernelSem::signal(){
	if(val++<0){
		deblock();
	}
}

void KernelSem::block(){
	Timer::running->myStatus=BLOCKED;
	blockedSem->put(Timer::running);
	dispatch();
}

void KernelSem::deblock(){
	PCB	*temp=blockedSem->get();
	temp->myStatus=READY;
	Scheduler::put(temp);
}