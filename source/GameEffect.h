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
	friend Singleton< GameEffect >;   //エフェクトのサイズ、コマ間隔、ファイルの元の名前
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
    void call();//SceneManagerでループ毎に呼び出し

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