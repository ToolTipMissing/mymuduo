#ifndef currentthread_h
#define currentthread_h

#include<unistd.h>
#include<sys/syscall.h>

namespace CurrentThread {
	extern __thread int _tid;
	inline int tid() {
		if (_tid == 0) {
			_tid = static_cast<int>(::syscall(SYS_gettid));
		}
		return _tid;
	}
}

#endif 

