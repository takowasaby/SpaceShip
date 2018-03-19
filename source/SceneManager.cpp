#include "SceneManager.h"
#include "SampleScene1.h"
#include "SampleScene2.h"
#include "Error.h"
#include "Keyboard.h"
#include "Pad.h"
#include "Macro.h"

using namespace std;

SceneManager::SceneManager()
{
	Parameter parameter;
	_sceneStack.push(make_shared<SampleScene1>(this, parameter));
}

bool SceneManager::loop()
{
	Keyboard::getIns()->update();   //キーボードの更新
	Pad::getIns()->update();        //ジョイパッドの更新
	_sceneStack.top()->update();    //スタックのトップのシーンを更新
	_sceneStack.top()->draw();      //スタックのトップのシーンを描画
//	_fps.draw();                    //FPSの表示
	_fps.update();                  //設定したFPSになるように待機

	//
	clsDx();
	printfDx("%d", _sceneStack.size());
	//

	return true;
}

void SceneManager::onSceneChanged(const eScene scene, const Parameter & parameter, const bool stackClear)
{
	if (stackClear) {//スタッククリアなら
		while (!_sceneStack.empty()) {//スタックを全部ポップする(スタックを空にする)
			_sceneStack.pop();
		}
	}
	switch (scene) {
	case Sample1:
		_sceneStack.push(make_shared<SampleScene1>(this, parameter));
		break;
	case Sample2:
		_sceneStack.push(make_shared<SampleScene2>(this, parameter));
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
