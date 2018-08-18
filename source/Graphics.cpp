#include "Graphics.h"

int Graphics::getHandle(const std::string& filename)
{
	auto itr = _graphics.find(filename);
	if (itr != _graphics.end())
	{
		return _graphics[filename];
	}

	itr = _priorityGraphics.find(filename);
	if (itr != _priorityGraphics.end())
	{
		return _priorityGraphics[filename];
	}

	return this->setHandle(filename);
}

int Graphics::getHandle(const std::string& filename, int priority)
{
	if (priority == 0)
	{
		auto itr = _graphics.find(filename);
		if (itr != _graphics.end())
		{
			return _graphics[filename];
		}
	}
	else if (priority == 1)
	{
		auto itr = _priorityGraphics.find(filename);
		if (itr != _priorityGraphics.end())
		{
			return _priorityGraphics[filename];
		}
	}
	return setHandle(filename, priority);
}

int Graphics::checkHandle(const std::string& filename, int priority)
{
    if (priority == 0)
    {
        auto itr = _graphics.find(filename);
        if (itr == _graphics.end())
            return false;
    }
    else
    {
        auto itr = _priorityGraphics.find(filename);
        if (itr == _priorityGraphics.end())
            return false;
    }
    return true;
}

int Graphics::setHandle(const std::string& filename)
{
    if (checkHandle(filename))
        return _graphics[filename];
	int ret = LoadGraph(filename.c_str());
	_graphics[filename] = ret;
	return ret;
}

int Graphics::setHandle(const std::string& filename, int priority)
{
    if (checkHandle(filename, priority))
    {
        if (priority == 0)
            return _graphics[filename];
        else
            return _priorityGraphics[filename];
    }
	int ret = LoadGraph(filename.c_str());
	if (priority == 0)
		_graphics[filename] = ret;
	else if (priority == 1)
		_priorityGraphics[filename] = ret;
	return ret;
}

int Graphics::setHandle(const std::string& filename, const std::string& url)
{
    if (checkHandle(filename))
        return _graphics[filename];
	int ret = LoadGraph(url.c_str());
	_graphics[filename] = ret;
	return ret;
}

int Graphics::setHandle(const std::string& filename, const std::string& url, int priority)
{
    if (checkHandle(filename, priority))
    {
        if (priority == 0)
            return _graphics[filename];
        else
            return _priorityGraphics[filename];
    }
	int ret = LoadGraph(url.c_str());
	if (priority == 0)
		_graphics[filename] = ret;
	else if (priority == 1)
		_priorityGraphics[filename] = ret;
	return ret;
}

void Graphics::getSize(int * graphicSizeX, int * graphicSizeY, int handle)
{
	GetGraphSize(handle, graphicSizeX, graphicSizeY);
}

void Graphics::lightReset()
{
	int num;
	for (auto itr = _graphics.begin(); itr != _graphics.end(); itr++)
	{
		num = DeleteGraph(itr->second);
		if (_debug)
			printfDx("DeleteReturn : %d\n", num);
	}
	_graphics.clear();
	return;
}

void Graphics::reset()
{
	int num;
	this->lightReset();
	for (auto itr = _priorityGraphics.begin(); itr != _priorityGraphics.end(); itr++)
	{
		num = DeleteGraph(itr->second);
		if (_debug)
			printfDx("DeleteReturn : %d\n", num);
	}
	_priorityGraphics.clear();
	return;
}
