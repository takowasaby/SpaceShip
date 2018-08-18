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

class GameEffect : public Singleton<GameEffect>
{
	GameEffect() = default;
	friend Singleton< GameEffect >;   //�G�t�F�N�g�̃T�C�Y�A�R�}�Ԋu�A�t�@�C���̌��̖��O
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
    void call();//SceneManager�Ń��[�v���ɌĂяo��

    int addEffectList(const std::string& unitname, GameEffectUnit *unit);//0-miss, 1-success
    int addEffectList(
        const std::string& unitname,
        const std::string& filename,
        const std::string& url,
        int frameNumber,
        int startFrame,
        int column,
        int row
    );
    int addEffectList(
        const std::string& unitname,
        const std::string& filename,
        int frameNumber,
        int startFrame,
        int column,
        int row
    );
    int makeEffect(const std::string& unitname, int posx, int posy, int totalTime);
    int makeEffect(const std::string& unitname, int posx, int posy, int totalTime, int width, int height);
    int makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime);
    int makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime, int width, int height);
    int makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height);
    int makeEffect(const std::string& unitname, const std::string& effectname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation);
    void setEffectPos(const std::string& effectname, int posx, int posy);
    void setEffectRepeate(const std::string& effectname, int repeateFlag);
    void setEffectRotation(const std::string& effectname, float rotation);
    int makeEffect(const std::string& effectname, const std::string& macroname);
    int makeEffect(const std::string& macroname);

    int makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime);
    int makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime, int width, int height);
    int makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height);
    int makeMacro(const std::string& unitname, const std::string& macroname, int posx, int posy, int totalTime, int repeatFlag, int width, int height, float rotation);
};