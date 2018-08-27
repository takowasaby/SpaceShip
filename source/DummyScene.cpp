#include "DummyScene.h"

DummyScene::DummyScene(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter)
{
}

void DummyScene::update()
{
	Parameter parameter;
	const bool stackClear = false;

	//DEBUG(oguni)
	//_implSceneChanged->onSceneChanged(eScene::BattleBoard, parameter, stackClear);
	_implSceneChanged->onSceneChanged(eScene::EnemySelect, parameter, stackClear);

	return;
}

void DummyScene::draw() const
{
}
