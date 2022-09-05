#include"Thread.h"

namespace CurrentThread{
	__thread int _tid = 0;
}

void* threadtask(void* param) {
	((Thread*)param)->run();
	return nullptr;
}

Thread::Thread(IRun0* run)
	:_run(run)
{}

void Thread::run() {
	_run->run0();
}

void Thread::start() {
	pthread_t tmp;
	::pthread_create(&tmp, 0, &threadtask, this);
}