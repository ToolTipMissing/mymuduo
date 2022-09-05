#include"Connection.h"

Connection::Connection(int sockfd,Eventloop* loop):
	_loop(loop)
{
	_channel = new Channel(sockfd,_loop);
	_channel->setcallback(this);
	_channel->update(EPOLLIN);
}

Connection::~Connection(){}

void Connection::readevents(){
	int sockfd = _channel->getfd();
	char buf[BUFFER_SIZE] = { 0 };
	int readlength = read(sockfd, buf, BUFFER_SIZE);
	if (readlength < 0) {
		std::cout << "read error" << std::endl;	
	}
	else if (readlength == 0) {
		std::cout << "client close:" << sockfd << std::endl;
		close(sockfd);
	}
	else {
		_inbuf.append(buf, readlength);
		_user->receivemessage(&_inbuf, this);
	}
}

void Connection::writeevents() {
	if (_channel->iswriting()) {
		int sockfd = _channel->getfd();
		int n = write(sockfd, _outbuf.c_str(), _outbuf.size());
		if (n < 0) {
			std::cout << "write error" << sockfd << std::endl;
			return;
		}
		_outbuf = _outbuf.substr(n, _outbuf.size());
		if (_outbuf.empty()) {
			_channel->disablewriting();
			Task* tmp = new Task(this);
			_loop->runinloop(tmp);
		}
	}
}

void Connection::sendmessage(const std::string& message) {
	int sockfd = _channel->getfd();
	int n = 0;
	if (_outbuf.empty()) {
		n = write(sockfd, message.c_str(), message.size());
		if (n<0) {
			std::cout << "write error" << sockfd << std::endl;
			return;
		}
	}
	if(n<static_cast<int>(message.size())){
		_outbuf += message.substr(n,message.size());
		_channel->update(EPOLLOUT);
	}
	Task* tmp = new Task(this, _outbuf, this);
	_loop->addtask(tmp);
}

void Connection::setuser(User* user) {
	_user = user;
}

void Connection::start() {
	_user->connectionestablished(this);
}

void Connection::run0() {
	_user->operationcomplete(this);
}

void Connection::run2(const std::string& str, void* param) {
	sendmessage(str);
}