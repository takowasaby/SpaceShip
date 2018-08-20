#define _USE_MATH_DEFINES

#include "Window.h"
#include "Graphics.h"
#include "DxLib.h"
#include <cmath>

Window::Window(Vector2 leftUp, Vector2 size) :
	_leftUp(leftUp),
	_size(size),
	_backs(static_cast<int>(eButtonState::STATE_SIZE))
{
	_line10 = Graphics::getIns()->getHandle("resource/image/UI/WinLine10.png");
	_line100 = Graphics::getIns()->getHandle("resource/image/UI/WinLine100.png");
	_curve = Graphics::getIns()->getHandle("resource/image/UI/curve.png");
	_edge = Graphics::getIns()->getHandle("resource/image/UI/WinLineEdge.png");
	_mark = Graphics::getIns()->getHandle("resource/image/UI/mark.png");

	for (int i = 0; i < static_cast<int>(eButtonState::STATE_SIZE); i++) {
		std::string filename = "resource/image/UI/g";
		filename += std::to_string(i + 1);
		filename += ".png";
		_backs[i] = Graphics::getIns()->getHandle(filename);
	}
}

void Window::draw(eButtonState state) const
{
	DrawExtendGraph(
		static_cast<int>(_leftUp.x()),
		static_cast<int>(_leftUp.y()),
		static_cast<int>(_leftUp.x() + _size.x()),
		static_cast<int>(_leftUp.y() + _size.y()),
		_backs[static_cast<int>(state)],
		TRUE
	);

	drawLine(_leftUp, Vector2(1.0f, 0.0f), _size.x());
	drawLine(_leftUp + Vector2(_size.x(), 0.0f), Vector2(0.0f, 1.0f), _size.y());
	drawLine(_leftUp + _size, Vector2(-1.0f, 0.0f), _size.x());
	drawLine(_leftUp + Vector2(0.0f, _size.y()), Vector2(0.0f, -1.0f), _size.y());
	drawMark();
}

void Window::drawLine(Vector2 start, Vector2 dir, float length) const
{
	double rotate = 0.0;
	if (dir.y() == 0.0f) {
		rotate = M_PI / 2.0;
	}
	Vector2 center = start;

	double curveRotate = static_cast<double>(dir.toAngle());
	DrawRotaGraph3(
		static_cast<int>(center.x()),
		static_cast<int>(center.y()),
		5, 5,
		1.0, 1.0,
		curveRotate, _curve, TRUE
	);
	center += dir * 5.0f;
	length -= 10.0f;

	int end;

	end = static_cast<int>(length) / 100;
	if (end)
	{
		center -= dir * 50.0f;

		for (int i = 0; i < end; i++)
		{
			center += dir * 100.0f;
			DrawRotaGraph3(
				static_cast<int>(center.x()),
				static_cast<int>(center.y()),
				39, 88,
				1.0, 1.0,
				rotate, _line100, TRUE
			);
		}

		center += dir * 50.0f;
	}

	end = (static_cast<int>(length) % 100) / 10;
	if (end) {
		center -= dir * 5.0f;

		for (int i = 0; i < end; i++)
		{
			center += dir * 10.0f;

			DrawRotaGraph3(
				static_cast<int>(center.x()),
				static_cast<int>(center.y()),
				5, 5,
				1.0, 1.0,
				rotate, _line10, TRUE
			);
		}

		center += dir * 5.0f;
	}
	
	double remLength = length - (static_cast<int>(length) / 10) * 10;
	
	//center += dir * (static_cast<float>(remLength) / 2.0f);
	DrawRotaGraph3(
		static_cast<int>(center.x()),
		static_cast<int>(center.y()),
		10, 5,
		remLength / 10.0, 1.0,
		curveRotate, _edge, TRUE
	);
}

void Window::drawMark() const
{
	if (_size.x() >= 100.0f && _size.y() >= 100.0f) {
		Vector2 center = _leftUp + _size - Vector2(30.0f, 0.0f);
		DrawRotaGraph(
			static_cast<int>(center.x()),
			static_cast<int>(center.y()),
			1.0, 0.0, _mark, TRUE
		);
	}
}
