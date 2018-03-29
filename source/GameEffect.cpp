#include "GameEffect.h"

void GameEffect::call()
{
    for (auto itr = _changableEffect.begin(); itr != _changableEffect.end(); itr++)
    {
        if (!itr->second.call())
        {
            _changableEffect.erase(itr);
        }
    }
    for (auto itr = _staticEffect.begin(); itr != _staticEffect.end(); itr++)
    {
        if (!itr->call())
        {
            _staticEffect.erase(itr);
        }
    }
}

int GameEffect::addEffectList(std::string * unitname, GameEffectUnit * unit)
{
    if(!unit->checkReady())
        return 0;
    _effectList[*unitname] = *unit;
    return 1;
}

int GameEffect::addEffectList(std::string * unitname, std::string * filename, std::string * url, int frameNumber, int startFrame, int column, int row)
{
    GameEffectUnit geu;
    geu.setALL(frameNumber, column, row, startFrame, filename, url);
    _effectList[*unitname] = geu;
    return 1;
}

int GameEffect::addEffectList(std::string * unitname, std::string * filename, int frameNumber, int startFrame, int column, int row)
{
    GameEffectUnit geu;
    geu.setALL(frameNumber, column, row, startFrame, filename);
    _effectList[*unitname] = geu;
    return 1;
}

int GameEffect::makeEffect(std::string * unitname, int posx, int posy, int totalTime)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    _staticEffect.push_back(ee);
    return 1;
}

int GameEffect::makeEffect(std::string * unitname, int posx, int posy, int totalTime, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    _staticEffect.push_back(ee);
    return 1;
}

int GameEffect::makeEffect(std::string * unitname, std::string * effectname, int posx, int posy, int totalTime)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    _changableEffect[*effectname] = ee;
    return 1;
}

int GameEffect::makeEffect(std::string * unitname, std::string * effectname, int posx, int posy, int totalTime, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    _changableEffect[*effectname] = ee;
    return 1;
}

int GameEffect::makeEffect(std::string * unitname, std::string * effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
    _changableEffect[*effectname] = ee;
    return 1;
}

int GameEffect::makeEffect(std::string * unitname, std::string * effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
    ee.setRotation(rotation);
    _changableEffect[*effectname] = ee;
    return 1;
}

void GameEffect::setEffectPos(std::string * effectname, int posx, int posy)
{
    _changableEffect[*effectname].setPosition(posx, posy);
}

void GameEffect::setEffectRepeate(std::string * effectname, int repeateFlag)
{
    _changableEffect[*effectname].setRepeatFlag(repeateFlag);
}

void GameEffect::setEffectRotation(std::string * effectname, float rotation)
{
    _changableEffect[*effectname].setRotation(rotation);
}

int GameEffect::makeEffect(std::string * effectname, std::string * macroname)
{
    _changableEffect[*effectname] = _macros[*macroname];
    return 1;
}

int GameEffect::makeEffect(std::string * macroname)
{
    _staticEffect.push_back(_macros[*macroname]);
    return 1;
}

int GameEffect::makeMacro(std::string * unitname, std::string * macroname, int posx, int posy, int totalTime)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    _macros[*macroname] = ee;
    return 1;
}

int GameEffect::makeMacro(std::string * unitname, std::string * macroname, int posx, int posy, int totalTime, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    _macros[*macroname] = ee;
    return 1;
}

int GameEffect::makeMacro(std::string * unitname, std::string * macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
    _macros[*macroname] = ee;
    return 1;
}

int GameEffect::makeMacro(std::string * unitname, std::string * macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[*unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
	ee.setRotation(rotation);
    _macros[*macroname] = ee;
    return 1;
}
