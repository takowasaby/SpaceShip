#include "SampleScene1.h"
#include <DxLib.h>
#include "SampleScene2.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"

//const char* SampleScene1::ParameterTagLabel = "ParameterTagLabel";

SampleScene2::SampleScene2(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter)
{
	_label = parameter.get(SampleScene1::ParameterTagLabel);
	if (_label == Parameter::Error) {
		ERR("�n���ꂽ���x�����s���ł�");
	}
}

void SampleScene2::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) != 0 && Keyboard::getIns()->getPressingCount(KEY_INPUT_1) == 1) {
		Parameter parameter;
		parameter.set(SampleScene1::ParameterTagLabel, 1);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Sample1, parameter, stackClear);
		return;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) != 0 && Keyboard::getIns()->getPressingCount(KEY_INPUT_2) == 1) {
		Parameter parameter;
		parameter.set(SampleScene1::ParameterTagLabel, 2);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Sample1, parameter, stackClear);
		return;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_B) == 1) {
		_implSceneChanged->onScenePoped();
		return;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_R) == 1) {
		Parameter parameter;
		parameter.set(SampleScene1::ParameterTagLabel, 0);
		const bool stackClear = true;
		_implSceneChanged->onSceneChanged(eScene::Sample1, parameter, stackClear);
		return;
	}

}

void SampleScene2::draw() const
{
	DrawString(100, 100, "Sample2", GetColor(255, 255, 255));
	DrawFormatString(100, 200, GetColor(255, 255, 255), "%d", _label);
}
