//File: prep.h
#ifndef _prep_h_
#define _prep_h_

#include "ivtentry.h"
#include "timer.h"

#define PREPAREENTRY(num,Old)\
		static void interrupt int##num(...);\
        IVTEntry entry##num = IVTEntry(0##x##num,&int##num);\
        void interrupt int##num(...){\
              entry##num.signal();\
              if(Old) entry##num.callOldIntR();\
        }
		
#endif

//prijavljuje unreachable code