#include"Timerqueue.h"

Timerqueue::Timerqueue(Eventloop* loop)
	:_loop(loop)
{
	_timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
	_timerchannel = new Channel(_timerfd, _loop);
	_timerchannel->setcallback(this);
	_timerchannel->update(EPOLLIN);
}

Timerqueue::~Timerqueue() {
	::close(_timerfd);
}

void Timerqueue::readevents() {
	Timestamp now(Timestamp::now());
	uint64_t one = 1;
	int n = read(_timerfd, &one, sizeof(one));
	if (n < static_cast<int>(sizeof(one))) {
		std::cout << "read eventfd error!" << std::endl;
	}
	std::vector<Timer*> expired = getexpired(now);
	for (auto& i : expired) {
		i->run();
		if (i->isrepeat()) {
			i->movetonext();
			_timers.insert(i);
		}
	}
}

void Timerqueue::writeevents() {}

struct timespec Timerqueue::howmuchtimefromnow(Timestamp t) {
	int64_t microseconds = t.microSecondsSinceEpoch() - Timestamp::now();
	if (microseconds < 100) {
		microseconds = 100;
	}
	timespec tmp;
	tmp.tv_sec = static_cast<time_t>(microseconds / Timestamp::kMicroSecsPerSec);
	tmp.tv_nsec = static_cast<long>((microseconds % Timestamp::kMicroSecsPerSec) * 1000);
	return tmp;
}

std::vector<Timer*> Timerqueue::getexpired(Timestamp now) {
	Timer tmp(nullptr, now, 0);
	auto i = _timers.lower_bound(&tmp);
	std::vector<Timer*> res;
	copy(_timers.begin(), i, back_inserter(res));
	_timers.erase(_timers.begin(), i);
	return res;
}

void Timerqueue::insert(Timer* timer) {
	bool beginchanged = 0;
	if (!_timers.empty()) {
		if (timer < *_timers.begin())beginchanged = 1;
	}
	else beginchanged = 1;
	_timers.insert(timer);
	if (beginchanged) {
		itimerspec tmp;
		memset(&tmp, 0, sizeof(tmp));
		tmp.it_value = howmuchtimefromnow(timer->getstamp());
		timerfd_settime(_timerfd, 0, &tmp, 0);
	}
}

void Timerqueue::addtimer(Task* task, Timestamp t, int interval) {
	Timer* tmp = new Timer(task, t, interval);
	_timers.insert(tmp);
}