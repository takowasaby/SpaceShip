#pragma once

#include "AbstractScene.h"
#include "Window.h"
#include "Button.h"
#include <memory>
#include <vector>

//�^�C�g�� > �`���[�g���A���I�� > CPU�G�͑I��
class EnemySelectScene : public AbstractScene {
public:
	EnemySelectScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~EnemySelectScene() = default;
	void update() override;
	void draw() const override;
private:
  const Window background;
  Button prevButton;
};
