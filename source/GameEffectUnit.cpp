#include "GameEffectUnit.h"

GameEffectUnit::GameEffectUnit():
    _effectFrameNumber(0),
    _effectFrameSizeWidth(0),
    _effectFrameSizeHeight(0),
    _effectStartFrame(0),
    _ready(0),
    _handle(0)
{
}



void GameEffectUnit::setALL(
    int EFrameNumber,
    int column,
    int row,
    int EStartFrame,
    const std::string& filename,
    const std::string& url
)
{
    _effectFrameNumber = EFrameNumber;
    _effectStartFrame = EStartFrame;
    setGraphics(url, filename);
    setFrameShape(column, row);
}

void GameEffectUnit::setALL(
    int EFrameNumber,
    int column,
    int row,
    int EStartFrame,
    const std::string& filename
)
{
    _effectFrameNumber = EFrameNumber;
    _effectStartFrame = EStartFrame;
    setGraphics(filename);
    setFrameShape(column, row);
}

int GameEffectUnit::checkReady()
{
    if (_ready == 1)
        return 1;
    if (_effectFrameSizeWidth != 0 &&
        _effectFrameSizeHeight != 0 &&
        _handle != 0
        )
    {
        _ready = 1;
        return 1;
    }
    return 0;
}

int GameEffectUnit::getHandle()
{
    if (!_ready)
        return -1;
    printfDx("Return handle is %d\n", _handle);
    return _handle;
}

void GameEffectUnit::setGraphics(const std::string& filename)
{
    _handle = Graphics::getIns()->setHandle(filename);
	printfDx("<%d>", _handle);
    _graphicFilename = filename;
    Graphics::getIns()->getSize(&_graphicSizeX, &_graphicSizeY, _handle);
    checkReady();
}


void GameEffectUnit::setGraphics(const std::string& url, const std::string& filename)
{
    _handle = Graphics::getIns()->setHandle(filename, url);
    _graphicFilename = filename;
    Graphics::getIns()->getSize(&_graphicSizeX, &_graphicSizeY, _handle);
    checkReady();
}

void GameEffectUnit::setFrameSize(int width, int height)
{
    _effectFrameSizeWidth = width;
    _effectFrameSizeHeight = height;
}

void GameEffectUnit::setFrameShape(int column, int row)
{
    _effectFrameSizeWidth = _graphicSizeX / column;
    _effectFrameSizeHeight = _graphicSizeY / row;
}

void GameEffectUnit::setFirstFramePosition(int firstFramePos)
{
    _effectStartFrame = firstFramePos;
}

void GameEffectUnit::reset()
{
    GameEffectUnit();
}

void GameEffectUnit::getGraphicRect(int * x, int * y, int * width, int * height, int *position, int curTime, int totalTime)
{
    int pos = ((_effectFrameNumber* curTime / totalTime) + _effectStartFrame);
    *position = pos;
    pos *= _effectFrameSizeWidth;
    *x = pos % _graphicSizeX;
    *y = ((int)(pos / _graphicSizeX)) * _effectFrameSizeHeight;
    *width  = _effectFrameSizeWidth;
    *height = _effectFrameSizeHeight;
}

GameEffectUnit::~GameEffectUnit()
{
}
