//File: timer.cpp
#include "timer.h"
#include "schedule.h"
#include <iostream.h>
#include <dos.h>
volatile int Timer::eksplicitno=0;
void interrupt (*Timer::oldRoutine)(...)=NULL;
Thread* Timer::starting=NULL;
IdleThread* Timer::idle=NULL;
PCB* Timer::running=NULL;




void Timer::inic(){
	lock();
	oldRoutine=getvect(0x08);   //sacuvamo staru
	setvect(0x08, timerInt);	//postavimo novu
	starting=new Thread(defaultStackSize, 1);
	starting->myPCB->myStatus=READY;
	running=(PCB*)starting->myPCB;
	idle=new IdleThread();
	idle->start();
	unlock();
}

void Timer::restore(){
	lock();

	setvect(0x08, oldRoutine);
	delete starting;
	
	unlock();
}


void interrupt Timer::timerInt(...){
	static volatile unsigned int tsp, tss; 
	static PCB *newPCB;
	
	if(!eksplicitno) {
		tick(); //mora da se poziva
		(*oldRoutine)();
		
		if(running->myTimeSlice!=0)
			running->myTimePassed++;
		if(running->myTimePassed < running->myTimeSlice || running->myTimeSlice==0)
				return;
		
	}	
	
	eksplicitno=0;
	if(running->myStatus==READY && running!=idle->myPCB){ //ako nije ready ne moze u scheduler, ni idle
		Scheduler::put((PCB*)running);
	}
	
	newPCB=Scheduler::get(); //uzimamo novi
	if(newPCB==NULL){        //ako su svi blokirani, postavljamo idle
		newPCB=idle->myPCB;
	}
	
	asm {	
		mov tsp, sp
		mov tss, ss	
		}

	running->sp = tsp;
	running->ss = tss; 	
			
	running=newPCB;

	tsp = running->sp;
	tss = running->ss; 
			
	running->myTimePassed=0;

	asm {
		mov sp, tsp   
		mov ss, tss
	} 
	return;
}






