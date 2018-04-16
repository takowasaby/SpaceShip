#pragma once
#include "BoardObject.h"
#include <list>
#include <memory>

class ObjectForTree {
public:
	std::shared_ptr<CQuadCell> _cell;
	std::shared_ptr<BoardObject> _object;
};

class CQuadCell {
public:
	//TODO _objactForTrees�ɃA�N�Z�X����֐��@�{�@���Z�b�g
	std::list<std::shared_ptr<ObjectForTree>>::iterator beginItr();

	void push(std::shared_ptr<ObjectForTree> object);
	void remove(std::list<std::shared_ptr<ObjectForTree>>::iterator itr);

private:
	std::list<std::shared_ptr<ObjectForTree>> _objectForTrees;
};