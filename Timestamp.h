#ifndef timestamp_h
#define timestamp_h

#include<sys/types.h>
#include<string>
#include"Declear.h"
#include<sys/time.h>

class Timestamp {
public:
	Timestamp(int64_t t=0);
	~Timestamp();
	bool valid();
	int64_t microSecondsSinceEpoch();
	static int64_t now();
	static const int kMicroSecsPerSec = 1000 * 1000;
	
private:
	int64_t _microSecondsSinceEpoch;
};

bool operator <(Timestamp a,Timestamp b);
bool operator ==(Timestamp a, Timestamp b);

#endif
