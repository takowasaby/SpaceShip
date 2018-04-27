#include "BattleBoardManager.h"
#include <algorithm>

using namespace std;

BattleBoardManager::BattleBoardManager()
{
}

void BattleBoardManager::addObject(Vector2 center, Vector2 velocity, int graphicHandle, float direction, char * campID, int CanExistTime)
{
	_boardObjects.push_back(make_shared<BoardObject>(center, velocity, graphicHandle, direction, campID, CanExistTime, _boardObjects.size(), this));
}

void BattleBoardManager::departObject(unsigned int num)
{
	auto itr = _boardObjects.begin();
	for (unsigned int i = 0; i < num; i++) ++itr;
	_boardObjects.erase(itr);
}

void BattleBoardManager::update()
{
	for_each(_boardObjects.begin(), _boardObjects.end(), 
		[](shared_ptr<BoardObject> object) { object->update(); });
}

void BattleBoardManager::draw() const
{
	for_each(_boardObjects.begin(), _boardObjects.end(), 
		[](shared_ptr<BoardObject> object) { object->draw(); });
}