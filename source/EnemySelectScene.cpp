#include <array>
#include <memory>
#include <utility>

#include "Vector2.h"
#include "EnemySelectScene.h"
#include "Define.h"
#include "Graphics.h"
#include "LightningBackground.h"
using namespace std;

EnemySelectScene::EnemySelectScene(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter),

	isSelectMode {false},

	//{left, top}, {width, height}
	backgroundWindow {{0.f, 0.f}, {static_cast<float>(Define::WIN_W), static_cast<float>(Define::WIN_H)}},
	selectboxWindow {{120.f, 450.f}, {400.f, 400.f}},
	previewWindow {{580.f, 200.f}, {650.f, 650.f}},

	prevButton {"prevButton",  {20.f, 45.f}, {230.f, 80.f}},
	nextButton {"nextButton", {260.f, 45.f}, {230.f, 80.f}},
	startSelectionButton {"startSelectionButton",  {120.f, 200.f}, {400.f, 100.f}},
	clearSelectionButton {"clearSelectionButton", {120.f, 310.f}, {400.f, 100.f}},

	enemyListButton {},
	selectedEnemyIds {}
{
	{
		const float width {400.f / static_cast<int>(enemyListButton.size())},
			height {400.f / static_cast<int>(enemyListButton[0].size())};
		for (int x = 0; x < enemyListButton.size(); ++x) {
			for (int y = 0; y < enemyListButton[x].size(); ++y) {
				enemyListButton[x][y] = make_unique<Button>(
					"Button"s + to_string(x) + "/"s + to_string(y),
					Vector2 {124.f + width * x, 454.f + height * y},
					Vector2 {width - 8, height - 8}
				);
			}
		}
	}




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
	removeLightningBgButton.addDrawer(ButtonColor); //debug

	for (const auto& btncol : enemyListButton) {
		for (const auto& btn : btncol) {
			btn->addDrawer(ButtonColor);
		}
	}
}

void EnemySelectScene::update()
{
	prevButton.update();
	nextButton.update();
	startSelectionButton.update();
	clearSelectionButton.update();
	removeLightningBgButton.update(); //debug

	for (const auto& btncol : enemyListButton) {
		for(const auto& btn : btncol){
			btn->update();
		}
	}


	if (prevButton.pressUp()) {
		_implSceneChanged->onScenePoped();
	}
	if (nextButton.pressUp()) {
		printfDx("\nそのボタンは未実装です。\n");
		//_implSceneChanged->onSceneChanged(eScene::Title, {}, false);
	}
	if (startSelectionButton.pressUp()) {
		isSelectMode = !isSelectMode;
		selectedEnemyIds.resize(0);
	}
	if (clearSelectionButton.pressUp()) {
		selectedEnemyIds.resize(0);
	}


	for (int x = 0; x < enemyListButton.size(); ++x) {
		for (int y = 0; y < enemyListButton[x].size(); ++y) {
			if (enemyListButton[x][y]->pressUp()) {
				auto p = find(selectedEnemyIds.begin(), selectedEnemyIds.end(), make_pair(x, y));
				if (isSelectMode) {
					if (p != selectedEnemyIds.end()) {
						//重複あり
						selectedEnemyIds.erase(p);
					} else if (selectedEnemyIds.size() <= 4) {
						//重複無し かつ 選択を追加可能
						selectedEnemyIds.push_back(make_pair(x, y));
					}
				} else {
					if (p != selectedEnemyIds.end()) {
						//重複あり
						selectedEnemyIds.resize(0);
					} else {
						//重複無し
						selectedEnemyIds.resize(0);
						selectedEnemyIds.push_back(make_pair(x, y));
					}
				}
			}
		}
	}

	if (removeLightningBgButton.pressUp()) { //debug
		isLightningBgUnabled = !isLightningBgUnabled;
	}
	if (!isLightningBgUnabled) { //debug
		lightningBg.add();
		lightningBg.update();
	}
}

void EnemySelectScene::draw() const
{
	if (!isLightningBgUnabled) { //debug
		lightningBg.draw();
	}


	backgroundWindow.draw();
	selectboxWindow.draw();
	previewWindow.draw();

	prevButton.draw();
	nextButton.draw();
	startSelectionButton.draw();
	clearSelectionButton.draw();
	removeLightningBgButton.draw(); //debug

	for (const auto& btncol : enemyListButton) {
		for (const auto& btn : btncol) {
			btn->draw();
		}
	}

	const float width {400.f / static_cast<int>(enemyListButton.size())},
		height {400.f / static_cast<int>(enemyListButton[0].size())};
	for (const auto& pos : selectedEnemyIds) {
		DrawExtendGraph(static_cast<int>(120 + pos.first * width),
			static_cast<int>(450 + pos.second * height),
			static_cast<int>(120 + pos.first * width + width),
			static_cast<int>(450 + pos.second * height + height),
			Graphics::getIns()->getHandle("resource/image/UI/g1.png"),
			TRUE
		);
	}

}
