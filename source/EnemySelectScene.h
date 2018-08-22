#pragma once

#include <memory>
#include <utility>

#include "AbstractScene.h"
#include "Window.h"
#include "Button.h"
#include "LightningBackground.h"
//タイトル > チュートリアル選択 > CPU敵艦選択
class EnemySelectScene : public AbstractScene {
public:
	EnemySelectScene(SceneChanger *impl, const Parameter& parameter);
	virtual ~EnemySelectScene() = default;
	void update() override;
	void draw() const override;
private:
	bool isSelectMode; //5つ選ぶ方

	const Window backgroundWindow,
	             selectboxWindow,
	             previewWindow;
	Button prevButton, 
	       nextButton,
	       startSelectionButton,
	       clearSelectionButton;

	std::vector<std::vector<std::unique_ptr<Button>>> enemyListButtons; //[x][y]
	std::vector<std::pair<int, int>> selectedEnemyPoss;


	//気分で作った電気的なエフェクトと、それを無効化するボタン
	LightningBackground lightningBg {};
	Button removeLightningBgButton {"removeLightningBgButton", {520.f, 45.f}, {230.f, 80.f}};
	bool isLightningBgUnabled {};



	void createEnemyListButtons();
	void setButtonImages();
	void updateButtons();
	void doButtonEvents();
	void doEnemyButtonEvent(int x, int y);
	void drawWindows() const;
	void drawButtons() const;
	Vector2 calcEnemyButtonPos(int x, int y) const;
	Vector2 calcEnemyButtonSize() const;
};
