#pragma once
#include "GameEffectUnit.h"

class GameEffectUnit;

class EachEffect
{
private:
    GameEffectUnit *_unit;		//所持するエフェクトユニットのポインタ
    int _derivationHandle;		//分割済みの画像ハンドル（callで更新）
    int _repeatFlag;			//エフェクトを繰り返し描画するかどうか
    int _rwidth;				//元の画像の横の長さ
    int _rheight;				//元の画像の縦の長さ

    int _posx, _posy;			//エフェクトを描画する画面上の座標
    float _width;				//実際に描画するエフェクトの横の長さ
    float _height;				//実際に描画するエフェクトの縦の長さ
    float _rotation;			//回転描画する角度	

    int _totalTime;				//エフェクトの寿命
    int _currentTime;			//エフェクトが生成されてからの時間
    int _beforePos;				//エフェクトの初めのフレーム

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

