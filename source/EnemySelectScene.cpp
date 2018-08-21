#include "EnemySelectScene.h"
#include "Define.h"
#include "Graphics.h"
#include <vector>
#include <array>
using namespace std;

EnemySelectScene::EnemySelectScene(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter),
	//{left, top}, {width, height}
	backgroundWindow {{0.f, 0.f}, {static_cast<float>(Define::WIN_W), static_cast<float>(Define::WIN_H)}},
	selectboxWindow {{120.f, 450.f}, {400.f, 400.f}},
	previewWindow {{580.f, 200.f}, {650.f, 650.f}},
	prevButton {"prevButton",  {20.f, 45.f}, {230.f, 80.f}},
	nextButton {"nextButton", {260.f, 45.f}, {230.f, 80.f}},
	startSelectionButton {"startSelectionButton",  {120.f, 200.f}, {400.f, 100.f}}, 
	clearSelectionButton {"clearSelectionButton", {120.f, 310.f}, {400.f, 100.f}}
{
	const array<int, 4> ButtonColor {
		Graphics::getIns()->getHandle("resource/image/UI/g4.png"),
		Graphics::getIns()->getHandle("resource/image/UI/g2.png"),
		Graphics::getIns()->getHandle("resource/image/UI/g4.png"),
		Graphics::getIns()->getHandle("resource/image/UI/g4.png")
	};

	prevButton.addDrawer(ButtonColor);
	nextButton.addDrawer(ButtonColor);
	startSelectionButton.addDrawer(ButtonColor);
	clearSelectionButton.addDrawer(ButtonColor);
}

void EnemySelectScene::update()
{
	prevButton.update();
	nextButton.update();
	startSelectionButton.update();
	clearSelectionButton.update();
	if (prevButton.pressUp()) {
		_implSceneChanged->onScenePoped();
	}
}

void EnemySelectScene::draw() const
{
	backgroundWindow.draw();
	selectboxWindow.draw();
	previewWindow.draw();

	prevButton.draw();
	nextButton.draw();
	startSelectionButton.draw();
	clearSelectionButton.draw();

}
