#include "GameEffect.h"

void GameEffect::call()
{
    for (auto itr = _changableEffect.begin(); itr != _changableEffect.end();itr++)
    {
        if (!itr->second.call())
        {
            itr = _changableEffect.erase(itr);
            if (itr == _changableEffect.end())
                break;
        }
    }
    for (auto itr = _staticEffect.begin(); itr != _staticEffect.end();itr++)
    {
        if (!itr->call())
        {
            itr = _staticEffect.erase(itr);
            if (itr == _staticEffect.end())
                break;
        }
    }
}

int GameEffect::addEffectList(const std::string& unitname, GameEffectUnit * unit)
{
    if(!unit->checkReady())
        return 0;
    _effectList[unitname] = *unit;
    return 1;
}

int GameEffect::addEffectList(const std::string& unitname, const std::string& filename, const std::string& url, int frameNumber, int startFrame, int column, int row)
{
    GameEffectUnit geu;
    geu.setALL(frameNumber, column, row, startFrame, filename, url);
    _effectList[unitname] = geu;
    return 1;
}

int GameEffect::addEffectList(const std::string& unitname, const std::string& filename, int frameNumber, int startFrame, int column, int row)
{
    GameEffectUnit geu;
    geu.setALL(frameNumber, column, row, startFrame, filename);
    _effectList[unitname] = geu;
    return 1;
}

int GameEffect::makeEffect(const std::string& unitname, int posx, int posy, int totalTime)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    _staticEffect.push_back(ee);
    return 1;
}

int GameEffect::makeEffect(const std::string& unitname, int posx, int posy, int totalTime, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    _staticEffect.push_back(ee);
    return 1;
}

int GameEffect::makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    _changableEffect[effectname] = ee;
    return 1;
}

int GameEffect::makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    _changableEffect[effectname] = ee;
    return 1;
}

int GameEffect::makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
    _changableEffect[effectname] = ee;
    return 1;
}

int GameEffect::makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
    ee.setRotation(rotation);
    _changableEffect[effectname] = ee;
    return 1;
}

void GameEffect::setEffectPos(const std::string& effectname, int posx, int posy)
{
    _changableEffect[effectname].setPosition(posx, posy);
}

void GameEffect::setEffectRepeate(const std::string& effectname, int repeateFlag)
{
    _changableEffect[effectname].setRepeatFlag(repeateFlag);
}

void GameEffect::setEffectRotation(const std::string& effectname, float rotation)
{
    _changableEffect[effectname].setRotation(rotation);
}

int GameEffect::makeEffect(const std::string& effectname, const std::string& macroname)
{
    _changableEffect[effectname] = _macros[macroname];
    return 1;
}

int GameEffect::makeEffect(const std::string& macroname)
{
    _staticEffect.push_back(_macros[macroname]);
    return 1;
}

int GameEffect::makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    _macros[macroname] = ee;
    return 1;
}

int GameEffect::makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    _macros[macroname] = ee;
    return 1;
}

int GameEffect::makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
    _macros[macroname] = ee;
    return 1;
}

int GameEffect::makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation)
{
    EachEffect ee;
    ee.setGameEffectUnit(&_effectList[unitname]);
    ee.setPosition(posx, posy);
    ee.setTotalTime(totalTime);
    ee.setSize(width, height);
    ee.setRepeatFlag(repeatFlag);
	ee.setRotation(rotation);
    _macros[macroname] = ee;
    return 1;
}
