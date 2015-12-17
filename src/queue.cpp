//File: queue.cpp

#include "queue.h"

Queue::Queue(){
	lock();
	first=NULL;
	length=0;
	unlock();
}

Queue::~Queue(){
	lock();
	Elem *temp;
	while(first!=NULL){
		temp=first;
		first=first->next;
		delete temp;
	}
	
	first=NULL; //za svaki slucaj
	length=0;
	unlock();
}

void Queue::put(PCB *p){
	lock();
	Elem *tek=first, *pret=NULL;
	while(tek && tek->pcb!=p){
		pret=tek;
		tek=tek->next;
	}
	if(tek!=NULL){
		unlock();
		return;
	}
	Elem *el= new Elem(); //ne na pocetku, prvo provera da vec ne postoji isti
	if(!first){
		first=el;
		first->next=NULL;
		first->pcb=p;
	}
	else{
		pret->next=el;
		pret->next->next=NULL;
		pret->next->pcb=p;
		
	}
	
	length++;
	unlock();
}

PCB* Queue::get(){
	if(!first) return NULL;
	lock();
	Elem *el=first;
	first=first->next;
	el->next=NULL;
	PCB* pcb=el->pcb; //pamtim samo pcb
	delete el; //da se ne bi gomilali
	length--;
	unlock();
	return pcb;
}