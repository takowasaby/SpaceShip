#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include "Singleton.h"

class Graphics : public Singleton<Graphics> 
{
	Graphics() = default;
	friend Singleton< Graphics >;

	//���̃N���X�ł́A���O��String�œn���Ƃ���ɍ������n���h��ID��ϊ����܂��B
	//���ɂ��̖��O�̃f�[�^���܂܂�Ă��Ȃ���΁A�V���Ƀ��[�h���A����΂��łɂ���n���h����n���B
private:
	std::map<std::string, int> _graphics;//�V�[���J�ڂ��Ƃɏ�������邱�Ƃ��O��
	std::map<std::string, int> _priorityGraphics;//�S�̂��I���܂ł͏�����Ȃ����Ƃ��O��
	int _debug;
public:
    int checkHandle(std::string *filename,int priority = 0);

	int getHandle(std::string *filename);
	int getHandle(std::string *filename, int priority);

	int setHandle(std::string *filename);
	int setHandle(std::string *filename, int priority);
	int setHandle(std::string *filename, std::string *url);
	int setHandle(std::string *filename, std::string *url, int priority);

	void getSize(int *graphicSizeX, int *graphicSizeY, int handele);
	void lightReset();//�d�v�x�̒Ⴂ���̂������Z�b�g����(priority = 0)
	void reset();//���ׂẴf�[�^����������
};
