#include"Timer.h"

Timer::Timer(Task* task, Timestamp t, int interval)
	:_task(task),
	_t(t),
	_interval(interval)
{}

Timer::~Timer(){}

Timestamp Timer::getstamp() {
	return _t;
}

bool Timer::isrepeat() {
	return _interval > 0;
}

void Timer::run() {
	_task->dotask();
}

void Timer::movetonext() {
	_t = Timestamp(Timestamp::now() + static_cast<int64_t>(_interval));
}

bool operator <(Timer a, Timer b) {
	return a.getstamp() < b.getstamp();
}

bool operator ==(Timer a, Timer b) {
	return a.getstamp() == b.getstamp();
}
