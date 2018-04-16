#include "CQuadTree.h"
#include "Macro.h"
#include <algorithm>

CQuadTree::CQuadTree(unsigned int level, float left, float top, float right, float bottom)
{
	if (level >= CQUADTREE_MAXLEVEL) ERR("ïsê≥Ç»4ï™ñÿê[ìxÇ≈Ç∑");

	for (int i = 0; i < CQUADTREE_MAXLEVEL; i++) {
		_numberToLiner[i] = (_numberToLiner[i - 1] - 1) / 3;
	}

	_level = level;
	_spaceSize = Vector2(right - left, bottom - top);
	_leftTop = Vector2(left, top);
	_unitSize = _spaceSize / (1 << _level);

	_dwCellNum = (_numberToLiner[level + 1] - 1) / 3;
	_cells.resize(_dwCellNum);

//	ObjectForTree oft;
//	*(oft._cell).erase(oft._cellNum);
}

void CQuadTree::sddObject(std::shared_ptr<BoardObject> spOBJ)
{
	std::shared_ptr<ObjectForTree> oft = std::make_shared<ObjectForTree>();
	oft->_object = spOBJ;
	registNewObject(
		spOBJ->center().x() - spOBJ->radius(),
		spOBJ->center().y() - spOBJ->radius(),
		spOBJ->center().x() + spOBJ->radius(),
		spOBJ->center().y() + spOBJ->radius(),
		oft);
	_ofts.push_back(oft);
}

void CQuadTree::update()
{
	registCheck();
	collisionCheck();
}

DWORD CQuadTree::getMortonNumber(Vector2 leftTop, Vector2 rightBottom) const
{
	DWORD LT = getPointElem(leftTop);
	DWORD RB = getPointElem(rightBottom);

	DWORD def = LT ^ RB;
	unsigned int hiLevel = 0;
	for (unsigned int i = 0; i < _level; i++) {
		def = (def >> 2) & 0x3;
		if (def != 0) hiLevel = i + 1;
	}

	DWORD spaceNum = RB >> (hiLevel * 2);
	DWORD addNum = (_numberToLiner[_level - hiLevel] - 1) / 3;
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
	std::for_each(_ofts.begin(), _ofts.end(), [this](std::shared_ptr<ObjectForTree> oft)
	{
		DWORD elem = getMortonNumber(
			oft->_object->center() - Vector2(oft->_object->radius(), oft->_object->radius()),
			oft->_object->center() + Vector2(oft->_object->radius(), oft->_object->radius())
		);
		if (oft->_cell != elem) {
			removeFromCell(oft);
			regist(elem, oft);
		}
	});
}

void CQuadTree::collisionCheck()
{
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
		return true;
	}
	return false;
}

void CQuadTree::removeFromCell(std::shared_ptr<ObjectForTree> oft)
{
	std::size_t cell = oft->_cell;
	_cells[cell].erase(oft->_cellNum);
	std::for_each(oft->_cellNum, _cells[cell].end(), [](std::shared_ptr<ObjectForTree> cellOft) {cellOft->_cellNum--; });
}
