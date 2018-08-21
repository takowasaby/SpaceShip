#pragma once

#include "AbstractScene.h"
#include "Window.h"
#include "Button.h"
#include <memory>
#include <vector>

//タイトル > チュートリアル選択 > CPU敵艦選択
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
