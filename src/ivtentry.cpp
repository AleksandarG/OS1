//File: ivtentry.cpp
#include "ivtentry.h"
#include <dos.h>

IVTEntry* IVTEntry::first=NULL;
IVTEntry* IVTEntry::last=NULL;

IVTEntry::IVTEntry(IVTNo ivtNo, intH nInt){
	lock();
	myEv=NULL;  //kasnije se dodeli
	numEntry=ivtNo;
	next=NULL;
	oldInt=getvect(ivtNo);
	setvect(ivtNo, nInt);
	if(first==NULL) 
		first=last=this;
    else {last->next = this;
          last = last->next;
    }
	unlock();
}

IVTEntry::~IVTEntry(){
	lock();
	setvect(numEntry, oldInt);
	IVTEntry* tek = first, *prev = NULL;
	while (tek && tek != this) {
		prev = tek; 
		tek = tek->next;
	}
	if(tek) {
		if(tek == first) first = first->next;
		if(tek == last) last = prev;
		
		if(prev!=NULL) prev->next = tek->next;
	}
	unlock();
}

void IVTEntry::signal(){
	lock();
	myEv->signal();
	unlock();
}

void IVTEntry::callOldIntR(){
	lock();
	(*oldInt)();
	unlock();
}

IVTEntry* IVTEntry::getEntry(IVTNo ivtNo){
	lock();
	IVTEntry* tek = first;
	while (tek && tek->numEntry != ivtNo) {
		tek = tek->next;
	}
	unlock();
	return tek;
	
}
