#pragma once

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
	const Window backgroundWindow,
	             selectboxWindow,
	             previewWindow;
	Button prevButton, 
	       nextButton,
	       startSelectionButton,
	       clearSelectionButton;

	//�C���ō�����d�C�I�ȃG�t�F�N�g�ƁA����𖳌�������{�^��
	LightningBackground lightningBg {};
	Button removeLightningBgButton {"removeLightningBgButton", {520.f, 45.f}, {230.f, 80.f}};
	bool isLightningBgUnabled {};
};
