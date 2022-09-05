#ifndef blockingqueue_h
#define blockingqueue_h

#include<deque>
#include"Mutex.h"
#include"Condition.h"

template<typename T>
class Blockingqueue {
public:
	Blockingqueue() :_cond(_mutex){}
	void put(const T& one) {
		Mutexlockguard lock(_mutex);
		_q.push_back(one);
		_cond.notify();
	}
	
	T take() {
		Mutexlockguard lock(_mutex);
		while (_q.empty()) {
			_cond.wait();
		}
		T res = _q.front();
		_q.pop_front();
		return res;
	}

private:
	std::deque<T> _q;
	Mutexlock _mutex;
	Condition _cond;
};

#endif