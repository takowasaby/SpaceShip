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
	//TODO _objactForTreesにアクセスする関数　＋　リセット


private:
	std::list<ObjectForTree> _objectForTrees;
};