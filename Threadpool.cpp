#include"Threadpool.h"

Threadpool::Threadpool(int poolsize) {
	_threads.resize(poolsize);
	for (int i = 0; i < poolsize; ++i) {
		_threads[i] = new Thread(this);
		_threads[i]->start();
	}
}

void Threadpool::addtask(Task* task) {
	_tasks.put(task);
}

void Threadpool::run0() {
	while (1) {
		_tasks.take()->dotask();
	}
}