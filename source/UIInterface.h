#pragma once
#include <string>

class UIInterface {
public:
	explicit UIInterface(const std::string& name) : _name(name) {};
	virtual ~UIInterface() = default;

	virtual void update() = 0;
	virtual void draw() const = 0;

	std::string& name() { return _name; }
	const std::string& name() const { return _name; }

private:
	std::string _name;
};