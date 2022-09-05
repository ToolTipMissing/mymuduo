#ifndef task_h
#define task_h

#include "IRun.h"
#include "Define.h"
#include<string>

class Task {
public:
	Task(IRun0* run0) 
		:_run0(run0),
		_run2(nullptr)
	{}

	Task(IRun2* run2, std::string str, void* param)
		:_run0(nullptr),
		_run2(run2),
		_str(str),
		_param(param)
	{}

	void dotask() {
		if (_run0) {
			_run0->run0();
		}
		else {
			_run2->run2(_str, _param);
		}
	}

private:
	IRun0* _run0;
	IRun2* _run2;
	std::string _str;
	void* _param;
};

#endif 

