#include"Tcpserver.h"
#include"Eventloop.h"

int main() {
	Eventloop* _loop = new Eventloop();
	User* _user = new User(_loop);
	_user->start();
	_loop->start();
	return 0;
}