#pragma once

#include <stack>
#include <memory>
#include "AbstractScene.h"
#include "SceneChanger.h"
#include "Fps.h"

class SceneManager final : public SceneChanger
{
public:
	SceneManager();
	~SceneManager() = default;
	bool loop();
	void onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear) override;
	void onScenePoped() override;
private:
	std::stack<std::shared_ptr<AbstractScene>> _sceneStack;
	Fps _fps;
};