#include "BattleBoardScene.h"
#include "Graphics.h"
#include <string>

BattleBoardScene::BattleBoardScene(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter)
{
	std::string str = "resource/image/ship.png";
	_battleBoardManager.addObject(
		Vector2(512,512),
		Vector2(1, 1),
		Graphics::getIns()->getHandle(&str),
		0,
		BoardObject::FRIEND_CAMP_ID,
		-1
	);
}

void BattleBoardScene::update()
{
	_battleBoardManager.update();
}

void BattleBoardScene::draw() const
{
	_battleBoardManager.draw();
}
