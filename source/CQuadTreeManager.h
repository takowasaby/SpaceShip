#pragma once
#include "CQuadTree.h"

const int CQUADTREE_LEVEL = 5;

class CQuadTreeManager {
public:
	CQuadTreeManager();

	void update();
	void addObject(std::shared_ptr<BoardObject> obj);

private:
	void collisionJudge(DWORD judgeCellNum);
	void judgeSameCell(std::shared_ptr<ObjectForTree> oft);
	void judgeOtherTreeCell(std::shared_ptr<ObjectForTree> oft);
	void objectStackPop(DWORD n);
	void objectStackPush(DWORD n);
	bool objectCollisionJudge(std::shared_ptr<BoardObject> obj1, std::shared_ptr<BoardObject> obj2);

	std::vector<std::shared_ptr<CQuadTree>> _trees;

	std::vector<std::shared_ptr<ObjectForTree>> _judgeObjectStack;
};