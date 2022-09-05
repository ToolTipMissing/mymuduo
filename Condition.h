#ifndef condition_h
#define condition_h

#include<pthread.h>
#include"Mutex.h"

class Condition {
public:
	Condition(Mutexlock& lock) 
		:_mutex(lock)
	{
		pthread_cond_init(&_condid,0);
	}
	~Condition() {
		pthread_cond_destroy(&_condid);
	}
	void wait() {
		pthread_cond_wait(&_condid, _mutex.getmutexid());
	}
	void notify() {
		pthread_cond_signal(&_condid);
	}
	void notifyall() {
		pthread_cond_broadcast(&_condid);
	}

private:
	Mutexlock& _mutex;
	pthread_cond_t _condid;
};

#endif 
