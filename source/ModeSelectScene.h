#pragma once

#include "AbstractScene.h"

class ModeSelectScene : public AbstractScene {
public:
	ModeSelectScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~ModeSelectScene() = default;
	void update() override;
	void draw() const override;
};