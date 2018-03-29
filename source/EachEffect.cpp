#include "EachEffect.h"



EachEffect::EachEffect()
{
    _currentTime = 0;
    _beforePos = -1;
    _repeatFlag = 0;
    _derivationHandle = -1;
}

void EachEffect::setGameEffectUnit(GameEffectUnit * inputUnit)
{
    _unit = inputUnit;
	_currentTime = 0;
	_beforePos = -1;
	int x, y, w, h, p;
	_unit->getGraphicRect(&x, &y, &w, &h, &p, _currentTime, 10);
	_rwidth = w;
	_rheight = h;
    _width = 1.0;
    _height = 1.0;
	_unit->checkReady();
}

void EachEffect::setRepeatFlag(int rflag)
{
    _repeatFlag = rflag;
}

void EachEffect::setSize(int w, int h)
{
    _width = (float)w / _rwidth;
    _height = (float)h / _rheight;
}

void EachEffect::setRotation(float rotation)
{
    _rotation = rotation;
}

void EachEffect::setTotalTime(int totalTime)
{
    _totalTime = totalTime;
}

void EachEffect::setPosition(int x, int y)
{
    _posx = x;
    _posy = y;
}

bool EachEffect::call()
{
    int x, y, w, h, p, handle;
    _unit->getGraphicRect(&x, &y, &w, &h, &p, _currentTime, _totalTime);
    if (p != _beforePos)
    {
        if (_beforePos != -1 && _derivationHandle != -1)
            DeleteGraph(_derivationHandle);
        if ((handle = _unit->getHandle()) != -1)
        {
            //printfDx("DrawAnswer:%d\n",DrawGraph(x, y, handle, TRUE));
            _derivationHandle = DerivationGraph(x, y, w, h, handle);
            printfDx("<%d>\n", _derivationHandle);
        }
        else
        {
			printfDx("<%d>", handle);
            printfDx("Cannot Read Unit Handle!\n");
        }
        _beforePos = p;
    }
    draw();
    _currentTime++;
    if (_repeatFlag == 1 && _currentTime == _totalTime)
    {
        _currentTime = 0;
    }
    if (_currentTime == _totalTime)
        return false;
    return true;
}

void EachEffect::draw()
{
    if (_derivationHandle != -1)
    {
        DrawRotaGraph3(
            _posx,
            _posy,
            _rwidth / 2,
            _rheight / 2,
            _width,
            _height,
            _rotation,
            _derivationHandle,
            TRUE
        );
    }
}

EachEffect::~EachEffect()
{
    if (_beforePos != -1)
        DeleteGraph(_derivationHandle);
}
