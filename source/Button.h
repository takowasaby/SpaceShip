#pragma once
#include "UIInterface.h"
#include "Vector2.h"
#include "eButtonState.h"
#include <functional>
//#include <forward_list>
#include <vector>
#include <array>
#include <memory>
#include "DxLib.h"

template<class T>
class CallFunc {
public:
	CallFunc(std::function<void(const std::string&)> func, T* thisptr) :
		_func(func),
		_thisptr(thisptr)
	{
	}
	void operator()(const std::string& buttonName){
		if (_thisptr == nullptr) return;
		_func(buttonName);
	}

private:
	std::function<void(const std::string&)> _func;
	T* _thisptr;
};

class Window;

class Button : public UIInterface {
public:
	Button(const std::string& name);
	Button(const std::string& name, Vector2 leftUp, Vector2 size);

	Button(const std::string& name, Vector2 leftUp, Vector2 size, const std::string& str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font);
	Button(const std::string& name, Vector2 leftUp, Vector2 size, const std::string& str, unsigned color = GetColor(255, 255, 255), int font = CreateFontToHandle(NULL, -1, -1, -1));

	Button(const std::string& name, float left, float up, float width, float height, const std::string& str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font);
	Button(const std::string& name, float left, float up, float width, float height, const std::string& str, unsigned color = GetColor(255, 255, 255), int font = CreateFontToHandle(NULL, -1, -1, -1));

	Button(const std::string& name, Vector2 leftUp, Vector2 size, const std::array<int, 4>& image);
	Button(const std::string& name, Vector2 leftUp, Vector2 size, int image);

	Button(const std::string& name, float left, float up, float width, float height, const std::array<int, 4>& image);
	Button(const std::string& name, float left, float up, float width, float height, int image);

	void addDrawer(const std::string& str, const std::array<unsigned, 4>& color, const std::array<int, 4>& font);
	void addDrawer(const std::string& str, unsigned color = GetColor(255, 255, 255), int font  = 0);

	void addDrawer(const std::array<int, 4>& image);
	void addDrawer(int image);

	void addFunc(std::function<void(const std::string&)>);

	void setWindow();

	void disable();
	void enable();

	void update() override;
	void draw() const override;

	bool pressDown() const;
	bool pressUp() const;
	bool pressing() const;
	int pressingCount() const;

	class ButtonDrawerInterface {
	public:
		virtual ~ButtonDrawerInterface() = default;
		virtual void draw(eButtonState) const = 0;
	};

private:
	eButtonState _buttonState;
	int _keepStateCount;
	eButtonState _beforeState;

	Vector2 _leftUp;
	Vector2 _size;

	std::vector<std::unique_ptr<ButtonDrawerInterface>> _drawers;
	std::unique_ptr<Window> _window;

	std::vector<std::function<void(const std::string&)>> _callFunctions;

	eButtonState decideButtonState() const;
	bool isInButton(int x, int y) const;

};