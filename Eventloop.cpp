#include"Eventloop.h"

Eventloop::Eventloop() 
	:_epoll(new Epoll()),
	_running(0),
	_loopthreadid(CurrentThread::tid())
{
	_timerqueue = new Timerqueue(this);
	_eventfd = ::eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK);
	_wakeupchannel = new Channel(_eventfd,this);
	_wakeupchannel->setcallback(this);
	_wakeupchannel->update(EPOLLIN);
}

Eventloop::~Eventloop(){
	::close(_eventfd);
}

void Eventloop::start() {
	while (1) {
		std::vector<Channel*> channels;
		_epoll->looping(&channels);
		for (auto& i : channels) {
			i->handle();
		}
		run();
	}
}

void Eventloop::update(Channel* channel) {
	_epoll->update(channel);
}


void Eventloop::readevents() {
	uint64_t one = 1;
	int n = read(_eventfd, &one, sizeof(one));
	if (n < static_cast<int>(sizeof(one))) {
		std::cout << "read eventfd error!" << std::endl;
	}
}

void Eventloop::writeevents() {}

void Eventloop::run() {
	std::vector<Task*>tmp;
	_running = 1;
	{
		Mutexlockguard guard(_mutex);
		swap(tmp, _tasks);
	}
	for (auto& i : tmp) {
		i->dotask();
	}
	_running = 0;
}

void Eventloop::runinloop(Task* task) {
	if (isloopthread()) {
		task->dotask();
	}
	else {
		addtask(task);
	}
}

void Eventloop::addtask(Task* task) {
	{
		Mutexlockguard guard(_mutex);
		_tasks.push_back(task);
	}
	if(_running|(!isloopthread()))wakeup();
}

void Eventloop::wakeup() {
	uint64_t one = 1;
	int n = write(_eventfd, &one, sizeof(one));
	if (n < static_cast<int>(sizeof(one))) {
		std::cout << "write eventfd error!" << std::endl;
	}
}

bool Eventloop::isloopthread() {
	return _loopthreadid == CurrentThread::tid();
}

void Eventloop::runat(Task* task, int t) {
	_timerqueue->addtimer(task, t, 0);
}

void Eventloop::runafter(Task* task, int delay) {
	Timestamp tmp(delay + Timestamp::now());
	_timerqueue->addtimer(task, tmp, 0);
}

void Eventloop::runevery(Task* task, int interval) {
	Timestamp tmp(interval + Timestamp::now());
	_timerqueue->addtimer(task, tmp, interval);
}
