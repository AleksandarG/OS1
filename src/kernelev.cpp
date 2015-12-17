//File: kernelev.cpp
#include "kernelev.h"
#include "timer.h"
#include "thread.h"
#include "ivtentry.h"


KernelEv::KernelEv(IVTNo ivtNo){
	val=0;
	owner=Timer::running;
	IVTEntry* temp=IVTEntry::getEntry(ivtNo);
	temp->myEv=this;
}

KernelEv::~KernelEv(){
	if(val==-1){
		val=0;
		owner->myStatus=READY;
		owner->myBlockedEv=NULL;
		Scheduler::put(owner);
	}
	
}

void KernelEv::wait(){
	if(owner!=Timer::running)return;  //samo vlasnik moze 
	if(--val<0){
		owner->myStatus=BLOCKED;
		owner->myBlockedEv=this;  //pamti blokirani event u pcb
		dispatch();
	}
}

void KernelEv::signal(){
	if(++val<=0){
		owner->myStatus=READY;
		owner->myBlockedEv=NULL;
		Scheduler::put(owner);    //moze ista nit posle dispatch da nastavi
	}
	else val=1;
	dispatch();
}