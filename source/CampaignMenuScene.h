#pragma once

#include "AbstractScene.h"

class CampaignMenuScene : public AbstractScene {
public:
	CampaignMenuScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~CampaignMenuScene() = default;
	void update() override;
	void draw() const override;
};