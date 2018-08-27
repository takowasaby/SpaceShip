#pragma once

#include <memory>
#include <utility>

#include "AbstractScene.h"
#include "Window.h"
#include "Button.h"
#include "LightningBackground.h"
//�^�C�g�� > �`���[�g���A���I�� > CPU�G�͑I��
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

	//�{�^���������ꂽ��Ԃ�Button::enable()�����s����ƃ{�^����������Ă��Ȃ���ԂɂȂ��Ă��܂����Ƃւ̑΍�B
	bool isClearSelectionButtonEnabled;
	bool isNextButtonEnabled;

	std::vector<std::vector<std::unique_ptr<Button>>> enemyListButtons; //[x][y]
	std::vector<std::pair<int, int>> selectedEnemyPoss;


	Vector2 calcEnemyButtonPos(int x, int y) const;
	Vector2 calcEnemyButtonSize() const;

	void goToNextScene();

	//�������p
	void setButtonImages();
	void createEnemyListButtons();

	//�`��
	void drawWindows() const;
	void drawButtons() const;

	//update
	void updateNextButtonEnableFlag();
	void updateClearSelectionButtonEnableFlag();

	void updateButtons();
	void doButtonEvents();
	void doEnemyButtonEvent(int x, int y);
};
