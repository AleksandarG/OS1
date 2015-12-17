//File: semaphor.cpp
#include "semaphor.h"
#include "pcb.h"
#include "kernsem.h"

Semaphore::Semaphore(int init){
	lock();
	myImpl=new KernelSem(init);
	unlock();
}

Semaphore::~Semaphore(){
	lock();
	delete myImpl;
	unlock();
}

void Semaphore::wait(){
	lock();
	myImpl->wait();
	unlock();
}

void Semaphore::signal(){
	lock();
	myImpl->signal();
	unlock();
}
	
int Semaphore::val() const{
	return myImpl->value();
} 