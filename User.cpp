#include"User.h"

User::User(Eventloop* loop){
	_server = new Tcpserver(loop);
	_threadpool = new Threadpool(3);
}

User::~User(){}

void User::start() {
	_server->setuser(this);
	_server->start();
}

void User::connectionestablished(Connection* connection) {
	std::cout << "connection established" << std::endl;
	send("connection established\n", connection);
}

void User::receivemessage(std::string* str,Connection* connection) {
	send(*str+"\n", connection);
}

void User::send(const std::string& str,Connection* connection) {
	std::cout << "tid:" << CurrentThread::tid() << " send a message" << std::endl;
	Task* tmp = new Task(connection, str, nullptr);
	_threadpool->addtask(tmp);
}

void User::run2(const std::string& str, void* param) {
	send(str+"\n", (static_cast<Connection*>(param)));
}

void User::operationcomplete(Connection* connection) {
	std::cout <<"operation complete" << std::endl;
}