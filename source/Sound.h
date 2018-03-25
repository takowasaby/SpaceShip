#pragma once
#include "DxLib.h"
#include "Singleton.h"
#include <string>
#include <map>

class Sound : public Singleton<Sound>
{
	Sound() = default;
	friend Singleton< Sound >;

	//���̃N���X�ł́A���O��String�œn���Ƃ���ɍ������n���h��ID��ϊ����܂��B
	//���ɂ��̖��O�̃f�[�^���܂܂�Ă��Ȃ���΁A�V���Ƀ��[�h���A����΂��łɂ���n���h����n���B
private:
	std::map<std::string, int> _bgm;
	std::map<std::string, int> _se;

	std::map<std::string, int> _priorityBgm;
	std::map<std::string, int> _prioritySe;

	int _bgmVolume;		//BGM�̃{�����[��(0�`255)
	int _seVolume;		//SE�̃{�����[��(0�`255)
public:
	int getBgmHandle(std::string *filename, int priority = -1);
	int getBgmHandle(std::string *filename, float volumeCorrection, int priority = -1);
	int setBgmHandle(std::string *filename, int priority = 0);
	int setBgmHandle(std::string *filename, std::string *url, int priority = 0);
	int setBgmHandle(std::string *filename, float volumeCorrection, int priority = 0);
	int setBgmHandle(std::string *filename, float volumeCorrection, std::string *url, int priority = 0);

	int getSeHandle(std::string *filename, int priority = -1);
	int getSeHandle(std::string *filename, float volumeCorrection, int priority = -1);
	int setSeHandle(std::string *filename, int priority = 0);
	int setSeHandle(std::string *filename, std::string *url, int priority = 0);
	int setSeHandle(std::string *filename, float volumeCorrection, int priority = 0);
	int setSeHandle(std::string *filename, float volumeCorrection, std::string *url, int priority = 0);

	void lightReset();  //�d�v�x�̒Ⴂ���̂������Z�b�g����(priority = 0)
	void reset();		//���ׂẴf�[�^���������� 

	int bgmVol() const { return _bgmVolume; }
	int& bgmVol() { return _bgmVolume; }

	int seVol() const { return _seVolume; }
	int& seVol() { return _seVolume; }

	bool setVolume(int bgmVolume, int seVolume);
};