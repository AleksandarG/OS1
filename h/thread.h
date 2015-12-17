//File: thread.h
#ifndef _thread_h
#define _thread_h

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;  //time, x 55ms
const Time defaultTimeSlice = 2; //default= 2*55ms
typedef int ID;

class PCB; 

class Thread{
public:
	void start();
	void waitToComplete();
	virtual ~Thread();

protected:
	friend class PCB;
	friend class Timer;
	friend class IdleThread;

	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run(){}

private:
	PCB* myPCB;
	
};

void dispatch();
extern void tick();   //obavezno pozivam!
#endif

