//File: main.cpp
#include <iostream.h>
#include "timer.h"
#include "thread.h"
#include "pcb.h"
#include <stdlib.h>



extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]){
	//Timer::inic();
	//if(PCB::running==NULL && PCB::starting==NULL)
	//	cout<<"jee "<<endl;
	//Timer *t=new Timer();
	//MainThread *mt=new MainThread();
	//mt->start();
	//dispatch();
	Timer::inic();
	int value=userMain(argc, argv);
	Timer::restore();
	//cout<<"Glavna kraj"<<endl;
	
	//Timer::restore();
	
	//for(int d=0; d<10000; d++)
		//	for(int k=0; k<10000;k++)
			//	for(int h=0;h<10000;h++);
//	delete t;
	//lock();
	//cout<<"Glavaaaa"<<value<<endl;
	//unlock();
	//delete mt;
	return value;
	//return 0;
}