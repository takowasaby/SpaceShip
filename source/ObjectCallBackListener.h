#pragma once
#include "Vector2.h"

class ObjectCallBackListener
{
public:
	ObjectCallBackListener() = default;
	virtual ~ObjectCallBackListener() = default;
	virtual void addObject(
		Vector2 center,
		Vector2 velocity,
		int graphicHandle,
		float direction,
		const char * campID,
		int CanExistTime
	) = 0;
	virtual void departObject(unsigned int num) = 0;
};

