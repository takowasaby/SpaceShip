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
	bool isPreviewMode;

	const Window backgroundWindow,
	             leftWindow,
	             rightWindow;

	Button prevButton, 
	       nextButton,
	       startSelectionButton,
	       clearSelectionButton;

	//ボタンが押された状態でButton::enable()を実行するとボタンが押されていない状態になってしまうことへの対策。
	bool isClearSelectionButtonEnabled;
	bool isNextButtonEnabled;

	std::vector<std::vector<std::unique_ptr<Button>>> enemyListButtons; //[x][y]
	std::vector<std::pair<int, int>> selectedEnemyPoss;


	Vector2 calcEnemyButtonPos(int x, int y) const;
	Vector2 calcEnemyButtonSize() const;

	void goToNextScene();

	//初期化用
	void setButtonImages();
	void createEnemyListButtons();

	//描画
	void drawWindows() const;
	void drawButtons() const;

	//update
	void updateNextButtonEnableFlag();
	void updateClearSelectionButtonEnableFlag();

	void updateButtons();
	void doButtonEvents();
	void doEnemyButtonEvent(int x, int y);
};
