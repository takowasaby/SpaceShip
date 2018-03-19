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
	Keyboard::getIns()->update();   //�L�[�{�[�h�̍X�V
	Pad::getIns()->update();        //�W���C�p�b�h�̍X�V
	_sceneStack.top()->update();    //�X�^�b�N�̃g�b�v�̃V�[�����X�V
	_sceneStack.top()->draw();      //�X�^�b�N�̃g�b�v�̃V�[����`��
//	_fps.draw();                    //FPS�̕\��
	_fps.update();                  //�ݒ肵��FPS�ɂȂ�悤�ɑҋ@

	//
	clsDx();
	printfDx("%d", _sceneStack.size());
	//

	return true;
}

void SceneManager::onSceneChanged(const eScene scene, const Parameter & parameter, const bool stackClear)
{
	if (stackClear) {//�X�^�b�N�N���A�Ȃ�
		while (!_sceneStack.empty()) {//�X�^�b�N��S���|�b�v����(�X�^�b�N����ɂ���)
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
		ERR("����͂��̂Ȃ��V�[�����Ă΂�܂���");
		break;
	}
}

void SceneManager::onScenePoped()
{
	if (_sceneStack.size() > 1) {
		_sceneStack.pop();
	}
}
