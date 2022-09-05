#include"Channel.h"

Channel::Channel(int fd, Eventloop* loop) :
	_added(0),
	_loop(loop),
	_fd(fd),
	_events(0),
	_revents(0),
	_callback(nullptr)
{}

Channel::~Channel() {};

void Channel::update(int events) {
	_events |= events;
	_loop->update(this);
}

void Channel::disablewriting(){
	_events &= ~EPOLLOUT;
	_loop->update(this);
}

void Channel::setcallback(IChannelcallback* callback) {
	_callback = callback;
}

void Channel::setrevents(int revents) {
	_revents = revents;
}

void Channel::handle() {
	if (_revents & EPOLLIN)_callback->readevents();
	if (_revents & EPOLLOUT)_callback->writeevents();
}

int Channel::getfd() {
	return _fd;
}

bool Channel::iswriting() {
	return _events & EPOLLOUT;
}

void Channel::add() {
	_added = 1;
}

bool Channel::isadded() {
	return _added;
}

int Channel::getevents() {
	return _events;
}