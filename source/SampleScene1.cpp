#include "SampleScene1.h"
#include <DxLib.h>
//#include "SampleScene2.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include "Sound.h"
#include "Graphics.h"

const char* SampleScene1::ParameterTagLabel = "ParameterTagLabel";

SampleScene1::SampleScene1(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter)
{
	_label = parameter.get(ParameterTagLabel);
//	if (_label == Parameter::Error) {
//		ERR("“n‚³‚ê‚½ƒŒƒxƒ‹‚ª•s³‚Å‚·");
//	}
	soundSet();
	graphSet();
	printfDx("%d, %d", handle, handle2);
}

void SampleScene1::update()
{
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) != 0 && Keyboard::getIns()->getPressingCount(KEY_INPUT_1) == 1) {
		Parameter parameter;
		parameter.set(ParameterTagLabel, 1);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Sample2, parameter, stackClear);

		StopSoundMem(handle);
		return;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_C) != 0 && Keyboard::getIns()->getPressingCount(KEY_INPUT_2) == 1) {
		Parameter parameter;
		parameter.set(ParameterTagLabel, 2);
		const bool stackClear = false;
		_implSceneChanged->onSceneChanged(eScene::Sample2, parameter, stackClear);
		
		StopSoundMem(handle);
		return;
	}

	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_B) == 1) {
		_implSceneChanged->onScenePoped();
		
		StopSoundMem(Sound::getIns()->getBgmHandle(&filename));
		return;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_R) == 1) {
		Parameter parameter;
		parameter.set(ParameterTagLabel, 0);
		const bool stackClear = true;
		_implSceneChanged->onSceneChanged(eScene::Sample2, parameter, stackClear);
		
		StopSoundMem(Sound::getIns()->getBgmHandle(&filename));
		return;
	}

}

void SampleScene1::draw() const
{
	DrawString(100, 100, "Sample1", GetColor(255, 255, 255));
	DrawFormatString(100, 200, GetColor(255, 255, 255), "%d", _label);
	DrawGraph(500, 500, handle2, TRUE);
}

void SampleScene1::soundSet()
{
	filename = "resource/music/1.wav";
	handle = Sound::getIns()->getBgmHandle(&filename, float(0.5));
	PlaySoundMem(handle, DX_PLAYTYPE_LOOP);

	printfDx("\n%d\n",CheckSoundMem(handle));
}

void SampleScene1::graphSet()
{
	filename = "resource/image/1.png";
	handle2 = Graphics::getIns()->getHandle(&filename);

	printfDx("\n%d\n", CheckSoundMem(handle));
}
