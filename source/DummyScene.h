#pragma once

#include "AbstractScene.h"
#include <string>

class DummyScene : public AbstractScene
{
public:

	DummyScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~DummyScene() = default;
	void update() override;
	void draw() const override;

};
