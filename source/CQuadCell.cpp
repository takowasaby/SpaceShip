#include "CQuadCell.h"

std::list<std::shared_ptr<ObjectForTree>>::iterator CQuadCell::beginItr()
{
	return _objectForTrees.begin();
}

void CQuadCell::push(std::shared_ptr<ObjectForTree> object)
{
	_objectForTrees.push_back(object);
}

void CQuadCell::remove(std::list<std::shared_ptr<ObjectForTree>>::iterator itr)
{
	_objectForTrees.erase(itr);
}
