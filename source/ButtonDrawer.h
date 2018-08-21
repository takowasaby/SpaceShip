#pragma once
#include "Button.h"

class StringButtonDrawer : public Button::ButtonDrawerInterface {
public:
	explicit StringButtonDrawer(Vector2 leftUp, Vector2 size, const std::string& str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font);
	explicit StringButtonDrawer(Vector2 leftUp, Vector2 size, const std::string& str, unsigned color, int font);

	void draw(eButtonState) const override;

private:
	Vector2 makeDrawPos(int i, Vector2 leftUp, Vector2 size);

	std::array<Vector2, 4> _drawStringPos;
	std::string _drawString;
	std::array<unsigned, 4> _drawStringColor;
	std::array<int, 4> _drawStringFont;

};

class ImageButtonDrawer : public Button::ButtonDrawerInterface {
public:
	explicit  ImageButtonDrawer(Vector2 leftUp, Vector2 size, const std::array<int, 4>& image);
	explicit  ImageButtonDrawer(Vector2 leftUp, Vector2 size, int image);

	void draw(eButtonState) const override;

private:
	Vector2 _leftUp;
	Vector2 _size;

	std::array<int, 4> _images;

};