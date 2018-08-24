#include "Button.h"
#include "ButtonDrawer.h"
#include "Window.h"
#include "Mouse.h"

Button::Button(const std::string& name) :
	UIInterface(name),
	_buttonState(eButtonState::disable),
	_keepStateCount(0),
	_beforeState(eButtonState::disable)
{
}

Button::Button(const std::string& name, Vector2 leftUp, Vector2 size) :
	UIInterface(name),
	_buttonState(eButtonState::neutral),
	_keepStateCount(0),
	_beforeState(eButtonState::neutral),
	_leftUp(leftUp),
	_size(size)
{
}

Button::Button(const std::string& name, Vector2 leftUp, Vector2 size, const std::string & str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font) :
	Button(name, leftUp, size)
{
	_drawers.push_back(std::make_unique<StringButtonDrawer>(_leftUp, _size, str, color, font));
}

Button::Button(const std::string& name, Vector2 leftUp, Vector2 size, const std::string& str, unsigned color, int font) :
	Button(name, leftUp, size)
{
	if(!font) _drawers.push_back(std::make_unique<StringButtonDrawer>(_leftUp, _size, str, color, CreateFontToHandle(NULL, -1, -1, -1)));
	_drawers.push_back(std::make_unique<StringButtonDrawer>(_leftUp, _size, str, color, font));
}

Button::Button(const std::string& name, float left, float up, float width, float height, const std::string & str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font) :
	Button(name, Vector2(left, up), Vector2(width, height), str, color, font)
{
}

Button::Button(const std::string& name, float left, float up, float width, float height, const std::string& str, unsigned color, int font) :
	Button(name, Vector2(left, up), Vector2(width, height), str, color, font)
{
}

Button::Button(const std::string& name, Vector2 leftUp, Vector2 size, const std::array<int, 4>& image) :
	Button(name, leftUp, size)
{
	_drawers.push_back(std::make_unique<ImageButtonDrawer>(_leftUp, _size, image));
}

Button::Button(const std::string& name, Vector2 leftUp, Vector2 size, int image) :
	Button(name, leftUp, size)
{
	_drawers.push_back(std::make_unique<ImageButtonDrawer>(_leftUp, _size, image));
}

Button::Button(const std::string& name, float left, float up, float width, float height, const std::array<int, 4>& image) :
	Button(name, Vector2(left, up), Vector2(width, height), image)
{
}

Button::Button(const std::string& name, float left, float up, float width, float height, int image) :
	Button(name, Vector2(left, up), Vector2(width, height), image)
{
}

void Button::addDrawer(const std::string & str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font)
{
	_drawers.push_back(std::make_unique<StringButtonDrawer>(_leftUp, _size, str, color, font));
}

void Button::addDrawer(const std::string & str, unsigned color, int font)
{
	_drawers.push_back(std::make_unique<StringButtonDrawer>(_leftUp, _size, str, color, font));
}

void Button::addDrawer(const std::array<int, 4>& image)
{
	_drawers.push_back(std::make_unique<ImageButtonDrawer>(_leftUp, _size, image));
}

void Button::addDrawer(int image)
{
	_drawers.push_back(std::make_unique<ImageButtonDrawer>(_leftUp, _size, image));
}

void Button::addFunc(std::function<void(const std::string&)> callFunction)
{
	_callFunctions.push_back(callFunction);
}

void Button::setWindow()
{
	_window = std::make_unique<Window>(_leftUp, _size);
}

void Button::disable()
{
	_buttonState = eButtonState::disable;
}

void Button::enable()
{
	_buttonState = eButtonState::neutral;
}

void Button::update()
{
	++_keepStateCount;

	if (_buttonState == eButtonState::disable) return;
	if (_beforeState != _buttonState)
	{
		_beforeState = _buttonState;
		_keepStateCount = 0;
	}
	_buttonState = decideButtonState();
}

void Button::draw() const
{
	if (_window.get() != nullptr) _window->draw(_buttonState);
	SetDrawArea(_leftUp.x(), _leftUp.y(), _leftUp.x() + _size.x(), _leftUp.y() + _size.y());
	for(int i = 0, max = _drawers.size(); i < max; i++)
		_drawers[i]->draw(_buttonState);
	SetDrawAreaFull();
}

bool Button::pressDown() const
{
	return _buttonState == eButtonState::press && !_keepStateCount;
}

bool Button::pressUp() const
{
	return _buttonState != eButtonState::press && _beforeState == eButtonState::press && _keepStateCount == 0;
}

bool Button::pressing() const
{
	return _buttonState == eButtonState::press;
}

int Button::pressingCount() const
{
	return _buttonState == eButtonState::press ? _keepStateCount : 0;
}

eButtonState Button::decideButtonState() const
{
	int x;
	int y;
	GetMousePoint(&x, &y);

	if (isInButton(x, y)) {
		int mouseInputCount = Mouse::getIns()->getPressingCount(MOUSE_INPUT_LEFT);
		if (mouseInputCount == 1) {
			for (auto func : _callFunctions) {
				func(name());
			}
			return eButtonState::press;
		}
		if (_buttonState == eButtonState::press && mouseInputCount)
			return eButtonState::press;
		else return eButtonState::choose;
	}
	else return eButtonState::neutral;

	return eButtonState();
}

bool Button::isInButton(int x, int y) const
{
	return 
		0 <= x - _leftUp.x() &&
		x - _leftUp.x() <= _size.x() &&
		0 <= y - _leftUp.y() &&
		y - _leftUp.y() <= _size.y();
}
