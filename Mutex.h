#ifndef mutex_h
#define mutex_h

#include<pthread.h>

class Mutexlock {
public:
	Mutexlock() {
		pthread_mutex_init(&_mutexid,0);
	}
	~Mutexlock() {
		pthread_mutex_destroy(&_mutexid);
	}
	void unlock() {
		pthread_mutex_unlock(&_mutexid);
	}
	void lock() {
		pthread_mutex_lock(&_mutexid);
	}
	pthread_mutex_t* getmutexid() {
		return &_mutexid;
	}

private:
	pthread_mutex_t _mutexid;
};

class Mutexlockguard {
public:
	Mutexlockguard(Mutexlock& mutex)
		:_lock(mutex)
	{
		_lock.lock();
	}
	~Mutexlockguard() {
		_lock.unlock();
	}

private:
	Mutexlock& _lock;
};

#endif 
