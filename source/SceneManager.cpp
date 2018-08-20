#include "SceneManager.h"
#include "SampleScene1.h"
#include "SampleScene2.h"
#include "BattleBoardScene.h"
#include "DummyScene.h"
#include "Error.h"
#include "Keyboard.h"
#include "Pad.h"
#include "Macro.h"
#include "Sound.h"
#include "GameEffect.h"

using namespace std;

SceneManager::SceneManager()
{
	Parameter parameter;
	_sceneStack.push(make_shared<DummyScene>(this, parameter));
	Sound::getIns()->setVolume(255, 255);
}

bool SceneManager::loop()
{
	Keyboard::getIns()->update();   //キーボードの更新
	Pad::getIns()->update();        //ジョイパッドの更新
	_sceneStack.top()->update();    //スタックのトップのシーンを更新
	_sceneStack.top()->draw();      //スタックのトップのシーンを描画
	_fps.draw();                    //FPSの表示
	_fps.update();                  //設定したFPSになるように待機
	//GameEffect::getIns()->call();	//エフェクトクラスの更新

	//
//	clsDx();
//	printfDx("%d", _sceneStack.size());
	//

	if (_nextScene) {
		_sceneStack.push(std::move(_nextScene));
	}

	if (_stackClear) {//スタッククリアなら
		while (!_sceneStack.empty()) {//スタックを全部ポップする(スタックを空にする)
			_sceneStack.pop();
		}
		_stackClear = false;
	}

	return true;
}

void SceneManager::onSceneChanged(const eScene scene, const Parameter & parameter, const bool stackClear)
{
	_stackClear = stackClear;
	switch (scene) {
	case Sample1:
		_nextScene = make_unique<SampleScene1>(this, parameter);
		break;
	case Sample2:
		_nextScene = make_unique<SampleScene2>(this, parameter);
		break;
	case BattleBoard:
		_nextScene = make_unique<BattleBoardScene>(this, parameter);
		break;
	default:
		ERR("あるはずのないシーンが呼ばれました");
		break;
	}
}

void SceneManager::onScenePoped()
{
	if (_sceneStack.size() > 1) {
		_sceneStack.pop();
	}
}
