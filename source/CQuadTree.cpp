#include "CQuadTree.h"
#include "Macro.h"
#include <algorithm>
#include <cmath>


CQuadTree::CQuadTree(unsigned int level, float left, float top, float right, float bottom)
{
	if (level >= CQUADTREE_MAXLEVEL) ERR("ïsê≥Ç»4ï™ñÿê[ìxÇ≈Ç∑");

	_numberToLiner[0] = 1;
	for (int i = 1; i < CQUADTREE_MAXLEVEL + 1; i++) {
		_numberToLiner[i] = _numberToLiner[i - 1] + pow(4, i-1);
	}

	_level = level;
	_spaceSize = Vector2(right - left, bottom - top);
	_leftTop = Vector2(left, top);
	_unitSize = _spaceSize / (1 << _level);

	_dwCellNum = _numberToLiner[level + 1];
	_cells.resize(_dwCellNum);

//	ObjectForTree oft;
//	*(oft._cell).erase(oft._cellNum);
}

void CQuadTree::addObject(std::shared_ptr<BoardObject> spOBJ)
{
	std::shared_ptr<ObjectForTree> oft = std::make_shared<ObjectForTree>();
	oft->_object = spOBJ;
	registNewObject(
		spOBJ->center().x() - spOBJ->radius(),
		spOBJ->center().y() - spOBJ->radius(),
		spOBJ->center().x() + spOBJ->radius(),
		spOBJ->center().y() + spOBJ->radius(),
		oft);
	//_ofts.push_back(oft);
}

std::size_t CQuadTree::getCellLength(DWORD n)
{
	return _cells[n].size();
}

std::list< std::shared_ptr <ObjectForTree> >::iterator CQuadTree::getCellBegin(DWORD n)
{
	return _cells[n].begin();
}

std::list< std::shared_ptr <ObjectForTree> >::iterator CQuadTree::getCellEnd(DWORD n)
{
	return _cells[n].end();
}

int CQuadTree::getNumberToLiner(int i)
{
	return _numberToLiner[i];
}

DWORD CQuadTree::getCellNum()
{
	return _dwCellNum;
}

void CQuadTree::update()
{
	registCheck();
	registWillAddOfts();
//	collisionCheck();
}

DWORD CQuadTree::getMortonNumber(Vector2 leftTop, Vector2 rightBottom) const
{
	DWORD LT = getPointElem(leftTop);
	DWORD RB = getPointElem(rightBottom);

	DWORD def = LT ^ RB;
	unsigned int hiLevel = 0;
	for (unsigned int i = 0; i < _level; i++) {
		def >>= 2;
		if ((def & 3) != 0)
			hiLevel = i + 1;
	}

	DWORD spaceNum = RB >> (hiLevel * 2);
	DWORD addNum = _numberToLiner[_level - hiLevel];
	spaceNum += addNum;

	if (spaceNum > _dwCellNum) return 0xffffffff;

	return spaceNum;
}

DWORD CQuadTree::get2DMortonNumber(WORD x, WORD y) const
{
	return (WORD) (BitUtils::BitSeparate32(x)) | (BitUtils::BitSeparate32(y) << 1);
}

DWORD CQuadTree::getPointElem(Vector2 position) const
{
	return get2DMortonNumber(
		(WORD)((position.x() - _leftTop.x()) / _unitSize.x()), 
		(WORD)((position.y() - _leftTop.y()) / _unitSize.y()));
}

void CQuadTree::registCheck()
{
	std::for_each(_cells.begin(), _cells.end(), [this](std::list< std::shared_ptr <ObjectForTree> >& cell)
	{
		std::for_each(cell.begin(), cell.end(), [this](std::shared_ptr<ObjectForTree> oft)
		{
			DWORD elem = getMortonNumber(
				oft->_object->center() - Vector2(oft->_object->radius(), oft->_object->radius()),
				oft->_object->center() + Vector2(oft->_object->radius(), oft->_object->radius())
			);
			if (oft->_cell != elem) {
				_cells[oft->_cell].erase(oft->_cellNum);
				_willAddOfts.push_back(oft);
				oft->_cell = elem;
			}
		});
	});
}

void CQuadTree::registWillAddOfts()
{
	std::for_each(_willAddOfts.begin(), _willAddOfts.end(), [this](std::shared_ptr<ObjectForTree> oft)
	{
		_cells[oft->_cell].push_back(oft);
	});
	_willAddOfts.clear();

	std::for_each(_cells.begin(), _cells.end(), [](std::list<std::shared_ptr<ObjectForTree>> ofts) {
		for (auto itr = ofts.begin(); itr != ofts.end(); itr++) {
			(*itr)->_cellNum = itr;
		}
	});
}

bool CQuadTree::registNewObject(float left, float top, float right, float bottom, std::shared_ptr<ObjectForTree> spOFT)
{
	DWORD elem = getMortonNumber(Vector2(left, top), Vector2(right, bottom));
	return regist(elem, spOFT);
}

bool CQuadTree::regist(DWORD elem, std::shared_ptr<ObjectForTree> spOFT)
{
	if (elem < _dwCellNum) {
		_cells[elem].push_back(spOFT);
		spOFT->_cellNum = _cells[elem].end();
		spOFT->_cell = elem;
	//	printf("%d", elem);
		return true;
	}
	return false;
}
/*
void CQuadTree::removeFromCell(std::shared_ptr<ObjectForTree> oft)
{
	std::size_t cell = oft->_cell;
	auto it = _cells[cell].erase(oft->_cellNum);
	std::for_each(it, _cells[cell].end(), [](std::shared_ptr<ObjectForTree> cellOft) {cellOft->_cellNum--; });
}*/