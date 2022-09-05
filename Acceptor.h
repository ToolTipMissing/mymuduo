#ifndef acceptor_h
#define acceptor_h

#include"Channel.h"
#include<arpa/inet.h>
#include"Define.h"
#include"Eventloop.h"
#include"Declear.h"
#include"IAcceptorcallback.h"

class Acceptor :public IChannelcallback {
public:
	Acceptor(Eventloop* loop);
	~Acceptor();
	void setcallback(IAcceptorcallback* callback);
	void start();
	virtual void readevents();
	virtual void writeevents();

private:
	void createlistenfd();
	int _listenfd;
	Eventloop* _loop;
	IAcceptorcallback* _callback;
	Channel* _channel;
};

#endif
