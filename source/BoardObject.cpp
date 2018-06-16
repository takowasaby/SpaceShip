#include "BoardObject.h"
#include "Graphics.h"
#include <cmath>
#include <cfloat>
#include <algorithm>

const char* BoardObject::NEUTRAL_CAMP_ID = "NEUTRAL_CAMP_ID";
const char* BoardObject::ENEMY_CAMP_ID = "ENEMY_CAMP_ID";
const char* BoardObject::FRIEND_CAMP_ID = "FRIEND_CAMP_ID";

BoardObject::BoardObject(
	Vector2 center,
	Vector2 velocity,
	int graphicHandle, 
	float direction, 
	const char * campID, 
	int CanExistTime,
	int manageListNum,
	ObjectCallBackListener* objectCallBackListener
) : 
	_center(center),
	_velocity(velocity),
	_graphicHandle(graphicHandle),
	_direction(direction),
	_campID(campID),
	_CanExistTime(CanExistTime),
	_manageListNum(manageListNum),
	_existCount(0),
	_radius(0)
{
	Graphics::getIns()->getSize(&_graphicSizeX, &_graphicSizeY, _graphicHandle);
}

bool BoardObject::update()
{
	move();
	rotate();
	if(_CanExistTime != -1) existJudge();
	std::for_each(_module.begin(), _module.end(), [&](std::shared_ptr<AbstractModule> module) { module->update(); });

	return true;
}

void BoardObject::draw() const
{
	DrawGraph((int)(_center.x() - (_graphicSizeX / 2)), (int)(_center.y() - (_graphicSizeY / 2)), _graphicHandle, TRUE);
}

void BoardObject::addModule(std::shared_ptr<AbstractModule> module)
{
	_module.push_back(module);
}

Vector2 BoardObject::center() const
{
	return _center;
}

Vector2 & BoardObject::center()
{
	return _center;
}

Vector2 & BoardObject::velocity()
{
	return _velocity;
}

Vector2 & BoardObject::acceleration()
{
	return _acceleration;
}

float BoardObject::direction() const
{
	return _direction;
}

float & BoardObject::direction()
{
	return _direction;
}

int & BoardObject::rotateCount()
{
	return _rotateCount;
}

float & BoardObject::goalDirection()
{
	return _goalDirection;
}

float BoardObject::radius() const
{
	return _radius;
}

int BoardObject::damage() const
{
	return _damage;
}

void BoardObject::move()
{
	_center += _velocity;
	_velocity += _acceleration;
}

void BoardObject::rotate()
{
	if (isRotate()) {
		_direction += (_goalDirection - _direction) / _rotateCount;
		--_rotateCount;
	}
}

bool BoardObject::isRotate()
{
	if (_goalDirection < 0.0f) return true;
	if (_rotateCount == 0) return false;
	if (_direction - _goalDirection < FLT_EPSILON) return false;
	return true;
}

void BoardObject::existJudge()
{
	++_existCount;
	if (_existCount == _CanExistTime) depart();
}

void BoardObject::depart()
{
	_objectCallBackListener->departObject(_manageListNum);
}
