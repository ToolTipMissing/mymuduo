#include"Timestamp.h"

Timestamp::Timestamp(int64_t t):
	_microSecondsSinceEpoch(t)
{}

Timestamp::~Timestamp(){}

bool Timestamp::valid() {
	return _microSecondsSinceEpoch > 0;
}

int64_t Timestamp::microSecondsSinceEpoch() {
	return _microSecondsSinceEpoch;
}

int64_t Timestamp::now() {
	struct timeval tmp;
	gettimeofday(&tmp, 0);
	int64_t seconds = tmp.tv_sec;
	return seconds * kMicroSecsPerSec + tmp.tv_usec;
}

bool operator <(Timestamp a, Timestamp b) {
	return a.microSecondsSinceEpoch() < b.microSecondsSinceEpoch();
}
bool operator ==(Timestamp a, Timestamp b) {
	return a.microSecondsSinceEpoch() == b.microSecondsSinceEpoch();
}