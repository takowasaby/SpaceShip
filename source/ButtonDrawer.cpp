#include "ButtonDrawer.h"

StringButtonDrawer::StringButtonDrawer(Vector2 leftUp, Vector2 size, const std::string& str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font) :
//	_drawStringPos(static_cast<int>(eButtonState::STATE_SIZE)),
	_drawString(str),
	_drawStringColor(color),
	_drawStringFont(font)
{
	for (int i = 0; i < static_cast<int>(eButtonState::STATE_SIZE); i++) {
		_drawStringPos[i] = makeDrawPos(_drawStringFont[i], leftUp, size);
	}
}

StringButtonDrawer::StringButtonDrawer(Vector2 leftUp, Vector2 size, const std::string & str, unsigned color, int font) :
	_drawString(str)
{
	Vector2 pos = makeDrawPos(font, leftUp, size);

	for (int i = 0; i < static_cast<int>(eButtonState::STATE_SIZE); i++) {
		_drawStringPos[i] = pos;
		_drawStringColor[i] = color;
		_drawStringFont[i] = font;
	}
}

StringButtonDrawer::~StringButtonDrawer()
{
	for (int i : _drawStringFont) DeleteFontToHandle(i);
}

void StringButtonDrawer::draw(eButtonState state) const
{
	DrawStringToHandle(
		static_cast<int>(_drawStringPos[static_cast<int>(state)].x()),
		static_cast<int>(_drawStringPos[static_cast<int>(state)].y()),
		_drawString.c_str(),
		_drawStringColor[static_cast<int>(state)],
		_drawStringFont[static_cast<int>(state)]
	);
}

Vector2 StringButtonDrawer::makeDrawPos(int font, Vector2 leftUp, Vector2 size)
{
	int stringWidth = GetDrawStringWidthToHandle(
		_drawString.c_str(),
		_drawString.size(),
		font
	);
	int stringHeight;
	GetFontStateToHandle(NULL, &stringHeight, NULL, font);
	stringHeight = static_cast<int>(stringHeight/* * 4.0 / 3.0*/);

	return leftUp + size / 2.0f - (Vector2(static_cast<float>(stringWidth), static_cast<float>(stringHeight)) / 2.0f);
}

ImageButtonDrawer::ImageButtonDrawer(Vector2 leftUp, Vector2 size, const std::array<int, 4>& image) :
	_leftUp(leftUp),
	_size(size),
	_images(image)
{
}

ImageButtonDrawer::ImageButtonDrawer(Vector2 leftUp, Vector2 size, int image) :
	_leftUp(leftUp),
	_size(size)
{
	for (int i = 0; i < static_cast<int>(eButtonState::STATE_SIZE); i++) {
		_images[i] = image;
	}
}

ImageButtonDrawer::~ImageButtonDrawer()
{
	for (int i : _images) DeleteGraph(i);
}

void ImageButtonDrawer::draw(eButtonState state) const
{
	Vector2 rightDown = _leftUp + _size;
  DrawExtendGraph(
		static_cast<int>(_leftUp.x()),
		static_cast<int>(_leftUp.y()),
		static_cast<int>(rightDown.x()),
		static_cast<int>(rightDown.y()),
		_images[static_cast<int>(state)],
		TRUE
	);
}
