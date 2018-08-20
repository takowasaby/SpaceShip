#pragma once

class UIInterface {
public:
	virtual ~UIInterface() = default;

	virtual void update() = 0;
	virtual void draw() const = 0;

};