#ifndef thread_h
#define thread_h

#include"IRun.h"
#include<pthread.h>
#include"Declear.h"
#include"Task.h"

class Thread {
public:
	Thread(IRun0* run);
	void start();
	void run();

private:
	IRun0* _run;
};

#endif
