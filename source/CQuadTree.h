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
	//std::list<std::shared_ptr<ObjectForTree>>::iterator _cellNum;
	std::size_t _cell;
	std::shared_ptr<BoardObject> _object;
};

class CQuadTree {
public:
	CQuadTree(unsigned int level, float left, float top, float right, float bottom);

	void addObject(std::shared_ptr<BoardObject> spOBJ);
	std::list< std::shared_ptr <ObjectForTree> >::iterator getCellBegin(DWORD n);
	std::list< std::shared_ptr <ObjectForTree> >::iterator getCellEnd(DWORD n);
	std::size_t getCellLength(DWORD n);
	//	bool createNewCell(DWORD elem);

	int getNumberToLiner(int i);
	DWORD getCellNum();

	void update();

private:
	int _numberToLiner[CQUADTREE_MAXLEVEL];

	Vector2 _spaceSize;
	Vector2 _leftTop;
	Vector2 _unitSize;
	unsigned int _level;
	DWORD _dwCellNum;

	//std::vector < std::shared_ptr<ObjectForTree> > _ofts;
	std::vector< std::list< std::shared_ptr <ObjectForTree> > > _cells;
	std::vector< std::shared_ptr <ObjectForTree> > _willAddOfts;

	DWORD getMortonNumber(Vector2 leftTop, Vector2 rightBottom) const;
	DWORD get2DMortonNumber(WORD x, WORD y) const
	{
		return (WORD)(BitSeparate32(x)) | (BitSeparate32(y) << 1);
	}
	DWORD getPointElem(Vector2 position) const
	{
		return get2DMortonNumber(
			(WORD)((position.x() - _leftTop.x()) / _unitSize.x()),
			(WORD)((position.y() - _leftTop.y()) / _unitSize.y()));
	}
	static DWORD BitSeparate32(DWORD n)
	{
		n = (n | (n << 8)) & 0x00ff00ff;
		n = (n | (n << 4)) & 0x0f0f0f0f;
		n = (n | (n << 2)) & 0x33333333;
		return (n | (n << 1)) & 0x55555555;
	}

	void registCheck();
	void registWillAddOfts();
	//	void collisionCheck();

	bool registNewObject(float left, float top, float right, float bottom, std::shared_ptr<ObjectForTree> spOFT);
	bool regist(DWORD elem, std::shared_ptr<ObjectForTree> spOFT);
	//	void removeFromCell(std::shared_ptr<ObjectForTree> obj);
};