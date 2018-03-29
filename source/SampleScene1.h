#pragma once

#include "AbstractScene.h"
#include <string>

class SampleScene1 : public AbstractScene
{
public:
	const static char* ParameterTagLabel;	//パラメーターのKey

	SampleScene1(SceneChanger *impl, const Parameter& parameter);
	virtual ~SampleScene1() = default;
	void update() override;
	void draw() const override;
	void soundSet();
	void graphSet();
	void effectSet();
    std::string getFilename() { return filename; }
private:
	int _label;
	std::string filename;
	int handle, handle2;
};