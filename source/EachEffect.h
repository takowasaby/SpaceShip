#pragma once
#include "GameEffectUnit.h"

class GameEffectUnit;

class EachEffect
{
private:
    GameEffectUnit *_unit;		//��������G�t�F�N�g���j�b�g�̃|�C���^
    int _derivationHandle;		//�����ς݂̉摜�n���h���icall�ōX�V�j
    int _repeatFlag;			//�G�t�F�N�g���J��Ԃ��`�悷�邩�ǂ���
    int _rwidth;				//���̉摜�̉��̒���
    int _rheight;				//���̉摜�̏c�̒���

    int _posx, _posy;			//�G�t�F�N�g��`�悷���ʏ�̍��W
    float _width;				//���ۂɕ`�悷��G�t�F�N�g�̉��̒���
    float _height;				//���ۂɕ`�悷��G�t�F�N�g�̏c�̒���
    float _rotation;			//��]�`�悷��p�x	

    int _totalTime;				//�G�t�F�N�g�̎���
    int _currentTime;			//�G�t�F�N�g����������Ă���̎���
    int _beforePos;				//�G�t�F�N�g�̏��߂̃t���[��

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

