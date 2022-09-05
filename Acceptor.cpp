#include"Acceptor.h"

Acceptor::Acceptor(Eventloop* loop):
	_loop(loop)
{}

Acceptor::~Acceptor(){}

void Acceptor::setcallback(IAcceptorcallback* callback) {
	_callback = callback;
}

void Acceptor::start() {
	createlistenfd();
	_channel = new Channel(_listenfd,_loop);
	_channel->setcallback(this);
	_channel->update(EPOLLIN);
}

void Acceptor::createlistenfd() {
	if ((_listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		std::cout << "socket error" << std::endl;
	}
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(11111);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	int on = 1;
	if (setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
		std::cout << "setsockopt error" << std::endl;
	}
	if (bind(_listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
		std::cout << "bind error" << std::endl;
	}
	if (listen(_listenfd, MAX_LISTENFD) == -1) {
		std::cout << "listen error" << std::endl;
	}
}

void Acceptor::readevents() {
	sockaddr_in cliaddr;
	int clilen = sizeof(cliaddr);
	int connfd = accept(_listenfd, (struct sockaddr*)&cliaddr, (socklen_t*)&clilen);
	if (connfd  == -1) {
		std::cout << "accept error" << std::endl;
	}
	else {
		std::cout << "connect fd:" << connfd << ",ip:" << inet_ntoa(cliaddr.sin_addr) << ",port:" << ntohs(cliaddr.sin_port) << std::endl;
	}
	_callback->newconnection(connfd);
}

void Acceptor::writeevents(){}