#pragma once
#include "DxLib.h"
#include "Singleton.h"
#include <string>
#include <map>

class Sound : public Singleton<Sound>
{
	Sound() = default;
	friend Singleton< Sound >;

	//このクラスでは、名前をStringで渡すとそれに合ったハンドルIDを変換します。
	//仮にその名前のデータが含まれていなければ、新たにロードし、あればすでにあるハンドルを渡す。
private:
	std::map<std::string, int> _bgm;
	std::map<std::string, int> _se;

	std::map<std::string, int> _priorityBgm;
	std::map<std::string, int> _prioritySe;

	int _bgmVolume;		//BGMのボリューム(0～255)
	int _seVolume;		//SEのボリューム(0～255)
public:
	//volumeCorrectionは個々のボリューム型への補正(0～1)
	//priorityはハンドルの重要度(0,1)
	int getBgmHandle(const std::string& filename, int priority = -1);
	int getBgmHandle(const std::string& filename, float volumeCorrection, int priority = -1);
	int setBgmHandle(const std::string& filename, int priority = 0);
	int setBgmHandle(const std::string& filename, std::string *url, int priority = 0);
	int setBgmHandle(const std::string& filename, float volumeCorrection, int priority = 0);
	int setBgmHandle(const std::string& filename, float volumeCorrection, std::string *url, int priority = 0);

	int getSeHandle(const std::string& filename, int priority = -1);
	int getSeHandle(const std::string& filename, float volumeCorrection, int priority = -1);
	int setSeHandle(const std::string& filename, int priority = 0);
	int setSeHandle(const std::string& filename, std::string *url, int priority = 0);
	int setSeHandle(const std::string& filename, float volumeCorrection, int priority = 0);
	int setSeHandle(const std::string& filename, float volumeCorrection, std::string *url, int priority = 0);

	void lightReset();  //重要度の低いものだけリセットする(priority = 0)
	void reset();		//すべてのデータを消去する 

	int bgmVol() const { return _bgmVolume; }
	int& bgmVol() { return _bgmVolume; }

	int seVol() const { return _seVolume; }
	int& seVol() { return _seVolume; }

	bool setVolume(int bgmVolume, int seVolume);
};