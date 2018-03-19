#pragma once

#include <list>
#include "Task.h"

class Fps : public Task{

public:
	Fps();
	bool update() override;
	void draw() const override;

private:
	std::list<int> _list;
	float _fps;
	unsigned _counter;

	void updateAverage();
	void regist();
	unsigned getWaitTime() const;

};