#ifndef timer_h
#define timer_h

#include"Timestamp.h"
#include"IRun.h"
#include"Task.h"
#include"Declear.h"

class Timer {
public:
	Timer(Task* run, Timestamp t, int interval);
	~Timer();
	Timestamp getstamp();
	bool isrepeat();
	void run();
	void movetonext();

private:
	Task* _task;
	Timestamp _t;
	int _interval;
};


bool operator <(Timer a, Timer b);
bool operator ==(Timer a, Timer b);

#endif
