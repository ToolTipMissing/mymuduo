#include"Tcpserver.h"

Tcpserver::Tcpserver(Eventloop* loop)
	:_acceptor(nullptr), 
	_loop(loop),
	_user(nullptr)
{}

Tcpserver::~Tcpserver() {}


void Tcpserver::newconnection(int sockfd) {
	Connection* pconnection = new Connection(sockfd,_loop);
	_connections[sockfd] = pconnection;
	pconnection->setuser(_user);
	pconnection->start();
}

void Tcpserver::start() {
	_acceptor = new Acceptor(_loop);
	_acceptor->setcallback(this);
	_acceptor->start();
}

void Tcpserver::setuser(User* user) {
	_user = user;
}