#pragma once
#include "Vector2.h"
#include "Button.h"
#include <vector>

class Window{
public:
	explicit Window(Vector2 leftUp, Vector2 size);

	void draw(eButtonState = eButtonState::neutral) const;

private:
	void drawLine(Vector2 start, Vector2 dir, float length) const;
	void drawMark() const;

	Vector2 _leftUp;
	Vector2 _size;

	int _line10;
	int _line100;
	int _curve;
	int _edge;
	int _mark;
	std::vector<int> _backs;
};