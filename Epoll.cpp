#include"Epoll.h"

Epoll::Epoll(){
	if ((_epollfd = epoll_create1(EPOLL_CLOEXEC)) == -1) {
		std::cout << "create epollfd error" << std::endl;
	}
}

Epoll::~Epoll(){}

void Epoll::looping(std::vector<Channel*>* channels) {
	int readyfds = epoll_wait(_epollfd, &*_events.begin(), MAX_EVENTS, -1);
	if (readyfds  == -1) {
		std::cout << "epoll_wait error" << std::endl;
		return;
	}
	for (int i = 0; i < readyfds; ++i) {
		Channel* pchannel = static_cast<Channel*>(_events[i].data.ptr);
		pchannel->setrevents(_events[i].events);
		channels->push_back(pchannel);
	}
}

void Epoll::update(Channel* pchannel) {
	struct epoll_event event;
	event.data.ptr = pchannel;
	event.events = pchannel->getevents();
	int sockfd = pchannel->getfd();
	if (pchannel->isadded()) {
		if (epoll_ctl(_epollfd, EPOLL_CTL_MOD, sockfd, &event) == -1) {
			std::cout << "epoll_ctl error" << std::endl;
		}
	}
	else {
		pchannel->add();
		if (epoll_ctl(_epollfd, EPOLL_CTL_ADD, sockfd, &event) == -1) {
			std::cout << "epoll_ctl error" << std::endl;
		}
	}
}