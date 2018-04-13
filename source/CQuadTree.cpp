#include "CQuadTree.h"
#include "Macro.h"

CQuadTree::CQuadTree(unsigned int level, float left, float top, float right, float bottom)
{
	if (level >= CQUADTREE_MAXLEVEL) ERR("•s³‚È4•ª–Ø[“x‚Å‚·");

	for (int i = 0; i < CQUADTREE_MAXLEVEL; i++) {
		_numberToLiner[i] = (_numberToLiner[i - 1] - 1) / 3;
	}
	_level = level;
	_spaceSize = Vector2(right - left, bottom - top);
	_leftTop = Vector2(left, top);
	_unitSize = _spaceSize / (1 << _level);
}
