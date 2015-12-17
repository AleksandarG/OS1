//File: idleth.cpp
#include "idleth.h"
#include "pcb.h"

IdleThread::IdleThread():Thread(256, 1){}

void IdleThread::run(){
	while(1);
}

void IdleThread::start(){ //ne ide u scheduler
	lock();
	myPCB->myStatus=READY;
	myPCB->createStack();
	unlock();
}