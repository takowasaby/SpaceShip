#pragma once

#include "AbstractScene.h"
#include "BattleBoardManager.h"

class BattleBoardScene : public AbstractScene {
private:
	BattleBoardManager _battleBoardManager;

public:
	BattleBoardScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~BattleBoardScene() = default;
	void update() override;
	void draw() const override;
};