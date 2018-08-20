#pragma once

#include "AbstractScene.h"

class MotherBoardSelectScene : public AbstractScene {
public:
	MotherBoardSelectScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~MotherBoardSelectScene() = default;
	void update() override;
	void draw() const override;
};