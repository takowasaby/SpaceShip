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
    //エフェクトのサイズ、コマ間隔、ファイルの元の名前
    //一度流すだけかどうか、繰り返すのか
    //オプションとして、スタート地点とコマの数を指定できる
    //表示する位置の調整も可能

    //使い方はまずUnitを登録、そこから、makeEffectで使うユニットの名前と、新しいEffectの名前を入力し実際に使う
    //名前を指定しない場合、変更が加わらない前提で勝手に動く
private:
    std::map<std::string, GameEffectUnit> _effectList;
    std::map<std::string, EachEffect> _changableEffect;//途中で中の情報を変える可能性があるとき
    std::list<EachEffect> _staticEffect;//最初において置いたら切れるまで流れて勝手に消える
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