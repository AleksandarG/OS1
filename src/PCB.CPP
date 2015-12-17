//File: pcb.cpp
#include "pcb.h"
#include "timer.h"
#include <stdlib.h>
#include <iostream.h>


PCB::PCB(StackSize stackSize, Time timeSlice, Thread *t){
	lock();
	myThread=t;
	myStatus=NEW;
    myTimePassed=0;
	myStackSize=stackSize;
	myStack=NULL;          //tek kad se startuje kreiramo stack
	myTimeSlice=timeSlice;
	myWaitQueue=new Queue();
	myBlockedEv=NULL;
	unlock();
}

PCB::~PCB(){
	lock();
	delete myWaitQueue;
	delete myStack;
	unlock();
}

void PCB::createStack(){
	lock();
	unsigned *stack;
	stack=new unsigned[myStackSize];
	myStack=stack;
	static unsigned oldSP, oldSS, newSP, newSS, newIP, newCS; //pomocne
	newSP=sp=FP_OFF(myStack+myStackSize);
	newSS=ss=FP_SEG(myStack+myStackSize);  //na vrh steka
	newIP=FP_OFF(&(wrapper));
	newCS=FP_SEG(&(wrapper));
	
	asm{
		mov oldSP, sp
		mov oldSS, ss
		mov sp, newSP
		mov ss, newSS  //prebacujemo se na stack novokreirane niti
		
		pushf
		pop ax
		or ax, 0x200
		push ax         //prvo psw
		
		mov ax, newCS   //pa pc
		push ax
		mov ax, newIP
		push ax
		
		mov ax, 0      //i ostali registri
		push ax
		push bx
		push cx
		push dx
		push es
		push ds
		push si
		push di
		push bp
		
		mov newSP, sp
		//mov newSS, ss  //ne treba, ne menja se
		mov sp, oldSP
		mov ss, oldSS   
	}
	this->sp=newSP;
	//ss=newSS;
	unlock();
}

void PCB::wrapper(){
	Timer::running->myThread->run();
	lock();
	Timer::running->myStatus = TERMINATED;
	
	while(Timer::running->myWaitQueue->empty()>0){
		PCB *temp = Timer::running->myWaitQueue->get();
		temp->myStatus =READY;
		Scheduler::put(temp);
	} 
	dispatch(); 
}

