#include "Mouse.h"
#include "DxLib.h"
#include <cmath>

bool Mouse::update()
{
	int nowMouseStatus;
	nowMouseStatus = GetMouseInput();

	for (int i = 0; i < MOUSE_KEY_NUM; i++) {
		if (nowMouseStatus & (1 << i)) {
			_releasingCount[i] = 0;
			_pressingCount[i]++;
		}
		else {
			_pressingCount[i] = 0;
			_releasingCount[i]++;
		}
	}

	return true;
}

int Mouse::getPressingCount(int mouseKeyCode)
{
	if (!isAvailableCode(mouseKeyCode)) {
		return -1;
	}
	return _pressingCount[static_cast<int>(std::log2(mouseKeyCode))];
}

int Mouse::getReleasingCount(int mouseKeyCode)
{
	if (!isAvailableCode(mouseKeyCode)) {
		return -1;
	}
	return _releasingCount[static_cast<int>(std::log2(mouseKeyCode))];
}

bool Mouse::isAvailableCode(int mouseKeyCode)
{
	return !(mouseKeyCode & mouseKeyCode - 1) && mouseKeyCode >= 1 && mouseKeyCode <= MOUSE_INPUT_5;
}
