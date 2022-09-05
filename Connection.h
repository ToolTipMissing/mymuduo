#ifndef connection_h
#define connection_h

#include"IRun.h"
#include"IChannelcallback.h"
#include"Declear.h"
#include"Define.h"
#include<string>
#include<unistd.h>
#include"Channel.h"
#include"User.h"

class Connection:public IChannelcallback,public IRun0,public IRun2 {
public:
	Connection(int sockfd,Eventloop* loop);
	~Connection();
	virtual void readevents();
	virtual void writeevents();
	void sendmessage(const std::string& message);
	void setuser(User* user);
	void start();

	virtual void run0();
	virtual void run2(const std::string& str, void* param);

private:
	Eventloop* _loop;
	User* _user;
	Channel* _channel;
	std::string _inbuf;
	std::string _outbuf;
};

#endif
