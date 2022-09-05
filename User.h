#ifndef user_h
#define user_h

#include"Tcpserver.h"
#include"Connection.h"
#include"Eventloop.h"
#include"Define.h"
#include<string>
#include"Declear.h"
#include"Threadpool.h"
#include"CurrentThread.h"

class Usersocks {
public:
	virtual void connectionestablished(Connection* connection) = 0;
	virtual void receivemessage(std::string* message,Connection* connection) = 0;
	virtual void operationcomplete(Connection* connection) = 0;
};

class User : public Usersocks,public IRun2{
public:
	User(Eventloop* loop);
	~User();
	void start();
	virtual void connectionestablished(Connection* connection);
	virtual void receivemessage(std::string* message,Connection* connection);
	virtual void operationcomplete(Connection* connection);
	void send(const std::string& message,Connection* connection);

	void run2(const std::string& str, void* param);
private:
	Tcpserver* _server;
	Threadpool* _threadpool;
};

#endif 
