#pragma once
#include "CQuadCell.h"
#include "Vector2.h"
#include "BitUtils.h"
#include <windef.h>
#include <vector>
#include <memory>

const int CQUADTREE_MAXLEVEL = 9;

class CQuadTree {
public:
	CQuadTree(unsigned int level, float left, float top, float right, float bottom);
	bool regist(float left, float top, float right, float bottom, ObjectForTree *spOFT);
	bool createNewCell(DWORD elem);

private:
	int _numberToLiner[CQUADTREE_MAXLEVEL];
	Vector2 _spaceSize;
	Vector2 _leftTop;
	Vector2 _unitSize;
	unsigned int _level;
	DWORD _dwCellNum;
	
	std::vector<std::shared_ptr<CQuadCell>> _cells;

	DWORD getMortonNumber(Vector2 leftTop, Vector2 rightBottom);
	DWORD get2DMortonNumber(WORD x, WORD y);
	DWORD getPointElem(Vector2 position)
};