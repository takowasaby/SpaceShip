#pragma once

#include "Singleton.h"
#include <array>

class Mouse final : public Singleton<Mouse> {

	Mouse() = default;
	friend Singleton<Mouse>;

public:

	bool update();//更新
	int getPressingCount(int mouseKeyCode);//mousKeyCodeのキーが押されているフレーム数を取得
	int getReleasingCount(int mouseKeyCode);//mouseKeyCodeのキーが離されているフレーム数を取得

private:
	static const int MOUSE_KEY_NUM = 5;//キー総数
	std::array<int, MOUSE_KEY_NUM> _pressingCount;//押されカウンタ
	std::array<int, MOUSE_KEY_NUM> _releasingCount;//離されカウンタ

	bool isAvailableCode(int mouseKeyCode);//mouseKeyCodeが有効なキー番号か問う
};
