#ifndef iacceptorcallback_h
#define iacceptorcallback_h

class IAcceptorcallback {
	public:
		virtual void newconnection(int listenfd) = 0;
};

#endif
