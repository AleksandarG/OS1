//File: queue.h
#ifndef _queue_h_
#define _queue_h_

#include "pcb.h"
#include <stdlib.h>
	
struct Elem{
	PCB *pcb;
	Elem *next;
	//Elem(PCB *p){//nije radilo
	//	pcb=p;
	//	next=NULL;
	//}
};

class Queue{
	
	Elem *first;
	
	int length;
public:
	Queue();
	~Queue();
	
	 int empty() const { return length;}
	void put(PCB* pcb);
	PCB* get();


		
};

#endif