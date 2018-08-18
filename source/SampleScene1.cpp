#include "SampleScene1.h"
#include <DxLib.h>
//#include "SampleScene2.h"
#include "Define.h"
#include "Keyboard.h"
#include "Macro.h"
#include "Sound.h"
#include "Graphics.h"
#include "GameEffect.h"

const char* SampleScene1::ParameterTagLabel = "ParameterTagLabel";

SampleScene1::SampleScene1(SceneChanger * impl, const Parameter & parameter) :
	AbstractScene(impl, parameter)
{
	_label = parameter.get(ParameterTagLabel);
//	if (_label == Parameter::Error) {
//		ERR("“n‚³‚ê‚½ƒŒƒxƒ‹‚ª•s³‚Å‚·");
//	}
    graphSet();
    soundSet();
	effectSet();
	printfDx("%d, %d", handle, handle2);
}

void SampleScene1::update()
{
    std::string fname = this->getFilename();
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
		
		StopSoundMem(Sound::getIns()->getBgmHandle(filename));
		return;
	}
	if (Keyboard::getIns()->getPressingCount(KEY_INPUT_R) == 1) {
		Parameter parameter;
		parameter.set(ParameterTagLabel, 0);
		const bool stackClear = true;
		_implSceneChanged->onSceneChanged(eScene::Sample2, parameter, stackClear);

        //printfDx("%s", filename.c_str());
        printfDx("%s", fname.c_str());
		StopSoundMem(Sound::getIns()->getBgmHandle(fname));
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
	printfDx("%s", filename.c_str());

	handle = Sound::getIns()->getBgmHandle(filename, float(0.5));
    printfDx("Sound:%d\n", PlaySoundMem(handle, DX_PLAYTYPE_LOOP));


	printfDx("\n%d\n",CheckSoundMem(handle));
}

void SampleScene1::graphSet()
{
	filename = "resource/effect/SampleEffect.png";
	handle2 = Graphics::getIns()->getHandle(filename);
    Graphics::getIns()->reset();
    handle2 = Graphics::getIns()->getHandle(filename);
    printfDx("handle2:%d\n", handle2);

	printfDx("\n%d\n", CheckSoundMem(handle));
}

void SampleScene1::effectSet()
{
	std::string effectFileName = "resource/effect/SampleEffect.png";
	std::string unitName = "Sample";
	GameEffect::getIns()->addEffectList(unitName, effectFileName, 13, 0, 5, 3);
	GameEffect::getIns()->makeEffect(unitName, 200, 200, 30);
    GameEffect::getIns()->makeEffect(unitName, 400, 200, 60);
}
