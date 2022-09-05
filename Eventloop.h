#ifndef eventloop_h
#define eventloop_h
	
#include<sys/epoll.h>
#include<sys/eventfd.h>
#include<unistd.h>
#include<vector>
#include"Declear.h"
#include"Task.h"
#include"IChannelcallback.h"
#include"Epoll.h"
#include"Timer.h"
#include"Channel.h"
#include"Timerqueue.h"
#include"Mutex.h"
#include"CurrentThread.h"

class Eventloop:public IChannelcallback {
public:
	Eventloop();
	~Eventloop();
	void start();
	void update(Channel* channel);
	void readevents();
	void writeevents(); 
	void runinloop(Task* task);
	void addtask(Task* task);
	void runat(Task* run,int t);
	void runafter(Task* run, int delay);
	void runevery(Task* run, int interval);

private:
	void wakeup();
	void run();
	bool isloopthread();
	Epoll* _epoll;
	int _eventfd;
	bool _running;
	Timerqueue* _timerqueue;
	Channel* _wakeupchannel;
	std::vector<Task*> _tasks;
	Mutexlock _mutex;
	int _loopthreadid;
};

#endif