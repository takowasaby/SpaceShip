#pragma once
#include "GameEffectUnit.h"

class GameEffectUnit;

class EachEffect
{
private:
    GameEffectUnit *_unit;
    int _derivationHandle;

    int _repeatFlag;
    int _rwidth;
    int _rheight;

    int _posx, _posy;
    float _width;
    float _height;
    float _rotation;

    int _totalTime;
    int _currentTime;
    int _beforePos;

public:
    EachEffect();
    void setGameEffectUnit(GameEffectUnit *inputUnit);
    void setRepeatFlag(int rflag);
    void setSize(int w, int h);
    void setRotation(float rotation);
    void setTotalTime(int totalTime);
    void setPosition(int x, int y);
    bool call();
    void draw();
    ~EachEffect();
};

