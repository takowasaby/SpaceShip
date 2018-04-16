#pragma once
//#include "CQuadCell.h"
#include "Vector2.h"
#include "BoardObject.h"
#include "BitUtils.h"
#include <vector>
#include <list>
#include <memory>

const int CQUADTREE_MAXLEVEL = 9;

class ObjectForTree {
public:
	std::list<std::shared_ptr<ObjectForTree>>::iterator _cellNum;
	std::size_t _cell;
	std::shared_ptr<BoardObject> _object;
};

class CQuadTree {
public:
	CQuadTree(unsigned int level, float left, float top, float right, float bottom);

	void sddObject(std::shared_ptr<BoardObject> spOBJ);
//	bool createNewCell(DWORD elem);

	void update();

private:
	int _numberToLiner[CQUADTREE_MAXLEVEL];
	Vector2 _spaceSize;
	Vector2 _leftTop;
	Vector2 _unitSize;
	unsigned int _level;
	DWORD _dwCellNum;
	
	std::list < std::shared_ptr<ObjectForTree> > _ofts;
	std::vector< std::list< std::shared_ptr<ObjectForTree> > > _cells;

	DWORD getMortonNumber(Vector2 leftTop, Vector2 rightBottom) const;
	DWORD get2DMortonNumber(WORD x, WORD y) const;
	DWORD getPointElem(Vector2 position) const;

	void registCheck();
	void collisionCheck();

	bool registNewObject(float left, float top, float right, float bottom, std::shared_ptr<ObjectForTree> spOFT);
	bool regist(DWORD elem, std::shared_ptr<ObjectForTree> spOFT);
	void removeFromCell(std::shared_ptr<ObjectForTree> obj);
};