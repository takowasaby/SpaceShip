#pragma once
#include "DxLib.h"
#include "GameEffectUnit.h"
#include "EachEffect.h"
#include <string>
#include <map>
#include <list>

class GameEffectUnit;
class EachEffect;

const unsigned int PLAY_ONCE = 1;
const unsigned int PLAY_REPEAT = 2;

class GameEffect
{
    //�G�t�F�N�g�̃T�C�Y�A�R�}�Ԋu�A�t�@�C���̌��̖��O
    //��x�����������ǂ����A�J��Ԃ��̂�
    //�I�v�V�����Ƃ��āA�X�^�[�g�n�_�ƃR�}�̐����w��ł���
    //�\������ʒu�̒������\

    //�g�����͂܂�Unit��o�^�A��������AmakeEffect�Ŏg�����j�b�g�̖��O�ƁA�V����Effect�̖��O����͂����ۂɎg��
    //���O���w�肵�Ȃ��ꍇ�A�ύX�������Ȃ��O��ŏ���ɓ���
private:
    std::map<std::string, GameEffectUnit> _effectList;
    std::map<std::string, EachEffect> _changableEffect;//�r���Œ��̏���ς���\��������Ƃ�
    std::list<EachEffect> _staticEffect;//�ŏ��ɂ����Ēu������؂��܂ŗ���ď���ɏ�����
    std::map<std::string, EachEffect> _macros;
public:
    void call();

    int addEffectList(std::string *unitname, GameEffectUnit *unit);//0-miss, 1-success
    int addEffectList(
        std::string *unitname,
        std::string *filename,
        std::string *url,
        int frameNumber,
        int startFrame,
        int column,
        int row
    );
    int addEffectList(
        std::string *unitname,
        std::string *filename,
        int frameNumber,
        int startFrame,
        int column,
        int row
    );
    int makeEffect(std::string *unitname, int posx, int posy, int totalTime);
    int makeEffect(std::string *unitname, int posx, int posy, int totalTime, int width, int height);
    int makeEffect(std::string *unitname, std::string *effectname, int posx, int posy, int totalTime);
    int makeEffect(std::string *unitname, std::string *effectname, int posx, int posy, int totalTime, int width, int height);
    int makeEffect(std::string *unitname, std::string *effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height);
    int makeEffect(std::string *unitname, std::string *effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation);
    void setEffectPos(std::string *effectname, int posx, int posy);
    void setEffectRepeate(std::string *effectname, int repeateFlag);
    void setEffectRotation(std::string *effectname, float rotation);
    int makeEffect(std::string *effectname, std::string *macroname);
    int makeEffect(std::string *macroname);

    int makeMacro(std::string *unitname, std::string *macroname, int posx, int posy, int totalTime);
    int makeMacro(std::string *unitname, std::string *macroname, int posx, int posy, int totalTime, int width, int height);
    int makeMacro(std::string *unitname, std::string *macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height);
    int makeMacro(std::string *unitname, std::string *macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation);
};