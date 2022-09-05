#ifndef epoll_h
#define epoll_h

#include<sys/epoll.h>
#include<vector>
#include"Channel.h"
#include"Define.h"
#include"Declear.h"

class Epoll {
public:
	Epoll();
	~Epoll(); 
	void looping(std::vector<Channel*>* channels);
	void update(Channel* pchannel);

private:
	int _epollfd;
	std::vector<struct epoll_event> _events = std::vector<struct epoll_event>(MAX_EVENTS);
};

#endif