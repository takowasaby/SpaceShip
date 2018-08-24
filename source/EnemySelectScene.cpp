#include <array>
#include <memory>
#include <utility>

#include "Vector2.h"
#include "EnemySelectScene.h"
#include "Define.h"
#include "Graphics.h"
#include "LightningBackground.h"
using namespace std;

//Vector2の各要素の乗算
static Vector2 Vector2Mul(const Vector2& v1, const Vector2& v2)
{
	return {v1.x() * v2.x(), v1.y() * v2.y()};
}

//Vector2の各要素の乗算
static Vector2 Vector2Div(const Vector2& v1, const Vector2& v2)
{
	return {v1.x() / v2.x(), v1.y() / v2.y()};
}



//{left, top, width, height}
static const Vector2 Selectbox_Window_Pos  {120.f, 450.f};
static const Vector2 Selectbox_Window_Size {400.f, 400.f};
static const Vector2 Preview_Window_Pos  {580.f, 200.f};
static const Vector2 Preview_Window_Size {650.f, 650.f};

static const Vector2 Prev_Button_Pos  {20.f, 45.f};
static const Vector2 Prev_Button_Size {230.f, 80.f};
static const Vector2 Next_Button_Pos  {260.f, 45.f};
static const Vector2 Next_Button_Size {230.f, 80.f};
static const Vector2 StartSelection_Button_Pos  {120.f, 200.f};
static const Vector2 StartSelection_Button_Size {400.f, 100.f};
static const Vector2 ClearSelection_Button_Pos  {120.f, 310.f};
static const Vector2 ClearSelection_Button_Size {400.f, 100.f};

static const pair<int, int> Enemy_Button_Num_XY {4, 5};
static const Vector2 Selectbox_Window_Grid_Size {Vector2Div(Selectbox_Window_Size, {static_cast<float>(Enemy_Button_Num_XY.first), static_cast<float>(Enemy_Button_Num_XY.second)})};
static const Vector2 Enemy_Button_Margin {4.f, 4.f};

Vector2 EnemySelectScene::calcEnemyButtonPos(int x, int y) const
{
	return Selectbox_Window_Pos + Enemy_Button_Margin + Vector2Mul(Selectbox_Window_Grid_Size, {static_cast<float>(x), static_cast<float>(y)});
}

Vector2 EnemySelectScene::calcEnemyButtonSize() const
{
	return Selectbox_Window_Grid_Size - Enemy_Button_Margin * 2;
}
void EnemySelectScene::createEnemyListButtons()
{
	enemyListButtons.resize(Enemy_Button_Num_XY.first);
	for (int x = 0; x < Enemy_Button_Num_XY.first; ++x) {
		enemyListButtons[x].resize(Enemy_Button_Num_XY.second);
		for (int y = 0; y < Enemy_Button_Num_XY.second; ++y) {
			enemyListButtons[x][y] = make_unique<Button>(
				"Button"s + to_string(x) + "/"s + to_string(y),
				calcEnemyButtonPos(x, y),
				calcEnemyButtonSize()
			);
		}
	}
}
void EnemySelectScene::setButtonImages()
{
	const array<int, 4> ButtonColor {
		Graphics::getIns()->getHandle("resource/image/UI/g4.png"),
		Graphics::getIns()->getHandle("resource/image/UI/g2.png"),
		Graphics::getIns()->getHandle("resource/image/UI/g4.png"),
		Graphics::getIns()->getHandle("resource/image/enemy-select-scene/tmp-disabled-button.png")
	};
	prevButton.addDrawer(ButtonColor);
	nextButton.addDrawer(ButtonColor);
	startSelectionButton.addDrawer(ButtonColor);
	clearSelectionButton.addDrawer(ButtonColor);
	removeLightningBgButton.addDrawer(ButtonColor); //debug

	for (const auto& btncol : enemyListButtons) {
		for (const auto& btn : btncol) {
			btn->addDrawer(ButtonColor);
		}
	}
	
}
EnemySelectScene::EnemySelectScene(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter),

	isSelectMode {false},

	//{left, top}, {width, height}
	backgroundWindow {{0.f, 0.f}, {static_cast<float>(Define::WIN_W), static_cast<float>(Define::WIN_H)}},
	selectboxWindow {Selectbox_Window_Pos, Selectbox_Window_Size},
	previewWindow {Preview_Window_Pos, Preview_Window_Size},

	prevButton {"prevButton", Prev_Button_Pos, Prev_Button_Size},
	nextButton {"nextButton", Next_Button_Pos, Next_Button_Size},
	startSelectionButton {"startSelectionButton", StartSelection_Button_Pos, StartSelection_Button_Size},
	clearSelectionButton {"clearSelectionButton", ClearSelection_Button_Pos, ClearSelection_Button_Size},

	isClearSelectionButtonEnabled {false},
	enemyListButtons {},
	selectedEnemyPoss {}
	
{
	createEnemyListButtons();
	setButtonImages();
}

void EnemySelectScene::updateButtons()
{
	prevButton.update();
	nextButton.update();
	startSelectionButton.update();
	clearSelectionButton.update();
	removeLightningBgButton.update(); //debug

	for (const auto& btncol : enemyListButtons) {
		for (const auto& btn : btncol) {
			btn->update();
		}
	}

	if (!isLightningBgUnabled) { //debug
		lightningBg.add();
		lightningBg.update();
	}
}
void EnemySelectScene::updateNextButtonEnableFlag()
{
	if (selectedEnemyPoss.size() < 5) {
		nextButton.disable();
		isNextButtonEnabled = false;
	} else if (!isNextButtonEnabled) { //Button::enable()を連続して実行するとボタンがクリックできない
		nextButton.enable();
		isNextButtonEnabled = true;
	}
}

void EnemySelectScene::updateClearSelectionButtonEnableFlag()
{
	if (selectedEnemyPoss.size() == 0) {
		clearSelectionButton.disable();
		isClearSelectionButtonEnabled = false;
	} else if(!isClearSelectionButtonEnabled) { //Button::enable()を連続して実行するとボタンがクリックできない
		clearSelectionButton.enable();
		isClearSelectionButtonEnabled = true;
	}
}


void EnemySelectScene::doButtonEvents()
{
	if (prevButton.pressUp()) {
		_implSceneChanged->onScenePoped();
		clsDx(); printfDx("\n「戻る」\n");
	}else if (nextButton.pressUp()) {
		clsDx(); printfDx("\n「決定」このボタンは、次のシーンのクラス名が分かったら作ります。\n");
		//_implSceneChanged->onSceneChanged(eScene::Title, {}, false);
	}else if (startSelectionButton.pressUp()) {
		isSelectMode = !isSelectMode;
		selectedEnemyPoss.resize(0);
		clsDx(); printfDx("\n「敵艦隊選択」5つのCPUの順序付き選択を開始。ボタンの名前を「敵艦隊選択中」に変更する。\n");
		if (isSelectMode) {
			printfDx("(現在は敵艦隊選択中です)\n");
		} else {
			printfDx("(現在は敵艦隊選択中ではありません。)\n");
		}
	}else if (clearSelectionButton.pressUp()) {
		selectedEnemyPoss.resize(0);
		clsDx(); printfDx("\n「艦隊選択クリア」\n");
	}else if (removeLightningBgButton.pressUp()) { //debug
		isLightningBgUnabled = !isLightningBgUnabled;
		clsDx(); printfDx("\nこのボタンはデバッグ用です。\n");
	} else {
		for (int x = 0; x < enemyListButtons.size(); ++x) {
			for (int y = 0; y < enemyListButtons[x].size(); ++y) {
				if (enemyListButtons[x][y]->pressUp()) {
					doEnemyButtonEvent(x, y);
				}
			}
		}
	}

}

void EnemySelectScene::doEnemyButtonEvent(int x, int y)
{
	auto p = find(selectedEnemyPoss.begin(), selectedEnemyPoss.end(), make_pair(x, y));
	if (isSelectMode) {
		//5個まで順序付きで選択
		if (p != selectedEnemyPoss.end()) {
			selectedEnemyPoss.erase(p);
		} else if (selectedEnemyPoss.size() <= 4) {
			selectedEnemyPoss.push_back(make_pair(x, y));
		}
	} else {
		//0個または1個を選択
		if (p != selectedEnemyPoss.end()) {
			selectedEnemyPoss.resize(0);
			clsDx(); //debug
		} else {
			selectedEnemyPoss.resize(0);
			selectedEnemyPoss.push_back(make_pair(x, y));
		}
		clsDx(); printfDx("\n右側の枠に選択した艦隊の画像が表示される予定です。\n");
	}
}

void EnemySelectScene::update()
{
	//軽い処理なので毎フレーム実行しても問題ない
	updateNextButtonEnableFlag();
	updateClearSelectionButtonEnableFlag();

	updateButtons();
	doButtonEvents();
}

void EnemySelectScene::drawWindows() const
{
	backgroundWindow.draw();
	selectboxWindow.draw();
	previewWindow.draw();
}

void EnemySelectScene::drawButtons() const
{
	prevButton.draw();
	nextButton.draw();
	startSelectionButton.draw();
	clearSelectionButton.draw();
	removeLightningBgButton.draw(); //debug
	for (const auto& btncol : enemyListButtons) {
		for (const auto& btn : btncol) {
			btn->draw();
		}
	}

	//選択されたボタンに画像を重ねる
	//TODO: Buttonクラスにaddした画像をremoveできるようになるか、チェックボックスが実装されたら、その機能で書き直す
	for (int i = 0; i < selectedEnemyPoss.size(); ++i) {
		const auto leftTop = calcEnemyButtonPos(selectedEnemyPoss[i].first, selectedEnemyPoss[i].second);
		const auto rightBottom = leftTop + calcEnemyButtonSize();
		if (isSelectMode) {
			DrawExtendGraph(static_cast<int>(leftTop.x()), static_cast<int>(leftTop.y()),
				static_cast<int>(rightBottom.x()), static_cast<int>(rightBottom.y()), Graphics::getIns()->getHandle("resource/image/enemy-select-scene/selected-" + to_string(i + 1) + ".png"), TRUE);
		} else {
			DrawExtendGraph(static_cast<int>(leftTop.x()), static_cast<int>(leftTop.y()),
				static_cast<int>(rightBottom.x()), static_cast<int>(rightBottom.y()), Graphics::getIns()->getHandle("resource/image/UI/g1.png"), TRUE);
		}
	}
}

void EnemySelectScene::draw() const
{
	if (!isLightningBgUnabled) { //debug
		lightningBg.draw();
	}

	drawWindows();
	drawButtons();
}
