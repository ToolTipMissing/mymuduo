#ifndef channel_h
#define channel_h

#include<iostream>
#include<sys/epoll.h>
#include"Eventloop.h"
#include"Declear.h"
#include"IChannelcallback.h"

class Channel {
public:
	Channel(int sockfd, Eventloop* loop);
	~Channel();
	void setcallback(IChannelcallback* callback);
	void setrevents(int revents);
	void update(int events);
	void handle();
	int getfd();
	void disablewriting();
	bool iswriting();
	void add();
	bool isadded();
	int getevents();

private:
	bool _added;
	Eventloop* _loop;
	int _fd;
	int _events;
	int _revents;
	IChannelcallback* _callback;
};

#endif