#include "DummyScene.h"

DummyScene::DummyScene(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter)
{
}

void DummyScene::update()
{
	Parameter parameter;
	const bool stackClear = false;
	_implSceneChanged->onSceneChanged(eScene::Sample1, parameter, stackClear);
	return;
}

void DummyScene::draw() const
{
}
