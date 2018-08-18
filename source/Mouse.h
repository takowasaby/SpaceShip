#pragma once

#include "Singleton.h"
#include <array>

class Mouse final : public Singleton<Mouse> {

	Mouse() = default;
	friend Singleton<Mouse>;

public:

	bool update();//�X�V
	int getPressingCount(int mouseKeyCode);//mousKeyCode�̃L�[��������Ă���t���[�������擾
	int getReleasingCount(int mouseKeyCode);//mouseKeyCode�̃L�[��������Ă���t���[�������擾

private:
	static const int MOUSE_KEY_NUM = 5;//�L�[����
	std::array<int, MOUSE_KEY_NUM> _pressingCount;//������J�E���^
	std::array<int, MOUSE_KEY_NUM> _releasingCount;//������J�E���^

	bool isAvailableCode(int mouseKeyCode);//mouseKeyCode���L���ȃL�[�ԍ����₤
};
