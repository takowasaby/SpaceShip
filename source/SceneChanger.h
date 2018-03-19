#pragma once

#include "EnumScene.h"
#include "AbstractScene.h"
#include "Parameter.h"

class SceneChanger
{
public:
	SceneChanger() = default;
	virtual ~SceneChanger() = default;
	virtual void onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear) = 0;
	virtual void onScenePoped() = 0;
};