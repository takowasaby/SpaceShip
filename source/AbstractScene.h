#pragma once

#include "SceneChanger.h"
#include "Parameter.h"
class SceneChanger;

class AbstractScene {
protected:
	SceneChanger* _implSceneChanged;
public:
	AbstractScene(SceneChanger* impl, const Parameter& parameter);
	virtual ~AbstractScene() = default;
	virtual void update() = 0;
	virtual void draw() const = 0;
};