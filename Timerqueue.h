#ifndef timerqueue_h
#define timerqueue_h

#include"Declear.h"
#include"Task.h"
#include"IChannelcallback.h"
#include"Eventloop.h"
#include"Channel.h"
#include"Timestamp.h"
#include"time.h"
#include<sys/timerfd.h>
#include<unistd.h>
#include<cstring>
#include<vector>
#include<set>

class Timerqueue :public IChannelcallback {
public:
	Timerqueue(Eventloop* loop);
	~Timerqueue();
	void addtimer(Task* task, Timestamp t, int interval);
	virtual void readevents();
	virtual void writeevents();
	struct timespec howmuchtimefromnow(Timestamp t);

private:
	std::vector<Timer*> getexpired(Timestamp now);
	void insert(Timer* timer);
	Eventloop* _loop;
	Channel* _timerchannel;
	int _timerfd;
	std::set<Timer*> _timers;
};


#endif
