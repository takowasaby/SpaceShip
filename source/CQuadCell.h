#pragma once
#include "BoardObject.h"
#include <list>

class ObjectForTree {
public:
	CQuadCell* _cell;
	BoardObject* _object;
	int _id;
};

class CQuadCell {
public:
	//TODO _objactForTrees�ɃA�N�Z�X����֐��@�{�@���Z�b�g


private:
	std::list<ObjectForTree> _objectForTrees;
};