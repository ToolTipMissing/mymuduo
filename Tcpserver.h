#ifndef tcpserver_h
#define tcpserver_h

#include"Acceptor.h"
#include"Connection.h"
#include"Eventloop.h"
#include"User.h"
#include<unordered_map>
#include"Declear.h"
#include"IAcceptorcallback.h"

class Tcpserver :public IAcceptorcallback {
public:
	Tcpserver(Eventloop* loop);
	~Tcpserver();
	void start();
	virtual void newconnection(int listenfd);
	void setuser(User* user);
private:
	Acceptor* _acceptor;
	Eventloop* _loop;
	User* _user;
	std::unordered_map<int,Connection*> _connections;
};

#endif