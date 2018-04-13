#pragma once
#include "ObjectCallBackListener.h"
#include "BoardObject.h"
#include <list>
#include <memory>

class BattleBoardManager : public ObjectCallBackListener {
public:
	BattleBoardManager();
	virtual ~BattleBoardManager() = default;

	virtual void addObject(
		Vector2 center,
		Vector2 velocity,
		int graphicHandle,
		float direction,
		char * campID,
		int CanExistTime
	);
	virtual void departObject(unsigned int num) override;

	void update();
	void draw() const;

private:
	std::list<std::shared_ptr<BoardObject>> _boardObjects;
};