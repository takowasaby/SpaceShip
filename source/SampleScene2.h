#pragma once

#include "AbstractScene.h"

class SampleScene2 : public AbstractScene
{
public:
//	const static char* ParameterTagLabel;	//パラメーターのKey

	SampleScene2(SceneChanger *impl, const Parameter& parameter);
	virtual ~SampleScene2() = default;
	void update() override;
	void draw() const override;
private:
	int _label;
};
