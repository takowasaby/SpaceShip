#pragma once

#include <iostream>
#include <string>
#include "Graphics.h"

class GameEffectUnit
{
    //エフェクトの種類だけこれを作成する。
	//Frameは描画する画像のうちの一コマ分
private:
    int _ready;
    int _handle;
    std::string _graphicFilename;//Graphics filename
    int _effectFrameNumber;//total frame number

    int _effectFrameSizeWidth;//frame width
    int _effectFrameSizeHeight;//frame height

    int _effectStartFrame;//count from leftop

    int _graphicSizeX;
    int _graphicSizeY;

public:
    GameEffectUnit();

    void setALL(
        int EFrameNumber,
        int column,
        int row,
        int EStartFrame,
        const std::string& filename,
        const std::string& url
        );
    void setALL(
        int EFrameNumber,
        int column,
        int row,
        int EStartFrame,
        const std::string& filename
    );
    int checkReady();
    int getHandle();
    void setGraphics(const std::string& filename);
    void setGraphics(const std::string& url, const std::string& filename);
    void setFrameSize(int width, int height);
    void setFrameShape(int column, int row);//横のマス数　縦のマス数
    void setFirstFramePosition(int firstFramePos);
    void reset();
    void getGraphicRect(int *x, int *y, int *width, int *height, int *position, int curTime, int totalTime);
    ~GameEffectUnit();
};

