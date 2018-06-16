#include "CQuadTreeManager.h"
#include <algorithm>
#include "Define.h"

using namespace std;

CQuadTreeManager::CQuadTreeManager()
{
	_trees.push_back(make_shared<CQuadTree>(CQUADTREE_LEVEL, 0.0f, 0.0f, static_cast<int>(Define::WIN_W), static_cast<int>(Define::WIN_H)));
	_trees.push_back(make_shared<CQuadTree>(CQUADTREE_LEVEL, 0.0f, 0.0f, static_cast<int>(Define::WIN_W), static_cast<int>(Define::WIN_H)));
}

void CQuadTreeManager::update()
{
	for_each(_trees.begin(), _trees.end(), [](shared_ptr<CQuadTree> cqt) { cqt->update(); });
	collisionJudge(0);
}

void CQuadTreeManager::addObject(std::shared_ptr<BoardObject> obj)
{
	if (obj->radius() == 0) _trees[1]->addObject(obj);
	else _trees[0]->addObject(obj);
}

void CQuadTreeManager::collisionJudge(DWORD judgeCellNum)
{
	for_each(
		_trees[0]->getCellBegin(judgeCellNum),
		_trees[0]->getCellEnd(judgeCellNum),
		[this]( shared_ptr<ObjectForTree> oft ) {
			judgeSameCell(oft);
			judgeOtherTreeCell(oft);
		}
	);
	if (((judgeCellNum << 2) + 4) < _trees[0]->getCellNum()) {
		for (int i = 0; i < 4; i++) {
			objectStackPush(judgeCellNum);
			collisionJudge((judgeCellNum << 2) + 1 + i);
		}
	}
	objectStackPop(judgeCellNum);
}

void CQuadTreeManager::judgeSameCell(std::shared_ptr<ObjectForTree> oft)
{
	for_each(
		oft->_cellNum,
		_trees[0]->getCellEnd(static_cast<DWORD>(oft->_cell)),
		[&oft, this](shared_ptr<ObjectForTree> otherOft) {
		if (objectCollisionJudge(oft->_object, otherOft->_object)) {
				//
				//Õ“Ëˆ—
				//
			}
		}
	);
}

void CQuadTreeManager::judgeOtherTreeCell(std::shared_ptr<ObjectForTree> oft)
{
	for_each(
		_trees[1]->getCellBegin(static_cast<DWORD>(oft->_cell)),
		_trees[1]->getCellEnd(static_cast<DWORD>(oft->_cell)),
		[&oft, this](shared_ptr<ObjectForTree> otherOft) {
		if (objectCollisionJudge(oft->_object, otherOft->_object)) {
			//
			//Õ“Ëˆ—
			//
		}
	}
	);
}

void CQuadTreeManager::objectStackPop(DWORD n)
{
	for (int i = 0; i < _trees[0]->getCellLength(n); i++) 
		_judgeObjectStack.pop_back();
}

void CQuadTreeManager::objectStackPush(DWORD n)
{
	for_each(
		_trees[0]->getCellBegin(n),
		_trees[0]->getCellEnd(n),
		[this](shared_ptr<ObjectForTree> oft) {
			this->_judgeObjectStack.push_back(oft);
		}
	);
}

bool CQuadTreeManager::objectCollisionJudge(std::shared_ptr<BoardObject> obj1, std::shared_ptr<BoardObject> obj2)
{
	return obj1->center().distance(obj2->center()) < obj1->radius() + obj2->radius();
}
