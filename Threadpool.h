#ifndef threadpool_h
#define threadpool_h

#include"Blockingqueue.h"
#include"Declear.h"
#include"Task.h"
#include"Thread.h"
#include"IRun.h"
#include<vector>

class Threadpool:public IRun0 {
public:
	Threadpool(int poolsize);
	void addtask(Task* task);
	virtual void run0();
private:
	Blockingqueue<Task*> _tasks;
	std::vector<Thread*> _threads;
};

#endif