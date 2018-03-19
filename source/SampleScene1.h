#pragma once

#include "AbstractScene.h"

class SampleScene1 : public AbstractScene
{
public:
	const static char* ParameterTagLabel;	//パラメーターのKey

	SampleScene1(SceneChanger *impl, const Parameter& parameter);
	virtual ~SampleScene1() = default;
	void update() override;
	void draw() const override;
private:
	int _label;
};