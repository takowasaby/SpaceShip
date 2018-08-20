#pragma once

#include "AbstractScene.h"

class TutorialModeSelectScene : public AbstractScene {
public:
	TutorialModeSelectScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~TutorialModeSelectScene() = default;
	void update() override;
	void draw() const override;
};