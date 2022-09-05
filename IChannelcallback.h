#ifndef ichannelcallback_h
#define ichannelcallback_h

class IChannelcallback {
public:
	virtual void readevents() = 0;
	virtual void writeevents() = 0;
};

#endif