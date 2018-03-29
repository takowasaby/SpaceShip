#pragma once

#include <iostream>
#include <string>
#include "Graphics.h"

class GameEffectUnit
{
    //�G�t�F�N�g�̎�ނ���������쐬����B
	//Frame�͕`�悷��摜�̂����̈�R�}��
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
        std::string *filename,
        std::string *url
        );
    void setALL(
        int EFrameNumber,
        int column,
        int row,
        int EStartFrame,
        std::string *filename
    );
    int checkReady();
    int getHandle();
    void setGraphics(std::string* filename);
    void setGraphics(std::string* url, std::string* filename);
    void setFrameSize(int width, int height);
    void setFrameShape(int column, int row);//���̃}�X���@�c�̃}�X��
    void setFirstFramePosition(int firstFramePos);
    void reset();
    void getGraphicRect(int *x, int *y, int *width, int *height, int *position, int curTime, int totalTime);
    ~GameEffectUnit();
};

