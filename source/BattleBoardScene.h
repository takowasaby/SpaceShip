#pragma once

#include "AbstractScene.h"

class BattleBoardScene : public AbstractScene {
private:

public:
	BattleBoardScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~BattleBoardScene() = default;
	void update() override;
	void draw() const override;
};