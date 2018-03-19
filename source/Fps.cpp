#include <DxLib.h>
#include "Fps.h"
#include "CalcUtils.h"

const static int LIST_LEN_MAX = 120;	//�ő�120�t���[���őҋ@�������v�Z����(2�ȏ�ɂ���)
const static int FPS = 60;				//FPS
const static int UPINTVL = 60;			//60�t���[���Ɉ�x�X�V����

Fps::Fps() :_counter(0), _fps(0) {}

bool Fps::update()
{
	_counter++;
	Sleep(getWaitTime());
	regist();
	if (_counter == UPINTVL) {
		updateAverage();
		_counter = 0;
	}
	return TRUE;
}

void Fps::draw() const
{
	if (_fps == 0) {
		return;
	}
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%04.1ffps", _fps);
}

void Fps::updateAverage()
{
	int len = (int)_list.size();
	if (len < LIST_LEN_MAX) {   //�܂����ς��v�Z���郌�x���ɂ܂ł��܂��Ă��Ȃ���Όv�Z���Ȃ�
		return;
	}
	int tookTime = _list.back() - _list.front();//LIST_LEN_MAX�t���[���ɂ�����������
	float average = (float)tookTime / (len - 1);//���ς����
	if (average == 0) {//0����h�~
		return;
	}
	_fps = CalcUtils::roundPoint(1000 / average, 2);//�����_��2�ʂŎl�̌ܓ�����
}

void Fps::regist()
{
	_list.push_back(GetNowCount());
	if (_list.size() > LIST_LEN_MAX) {
		_list.pop_front();
	}
}

unsigned Fps::getWaitTime() const
{
	int len = (int)_list.size();
	if (len == 0) {
		return 0;
	}
	int shouldTookTime = (int)(1000 / 60.f*(len));            //�v�Z�ォ����ׂ�����
	int actuallyTookTime = GetNowCount() - _list.front();   //���ۂɂ�����������
	int waitTime = shouldTookTime - actuallyTookTime;       //�v�Z�ォ����ׂ����� - ���ۂɂ����������ԁ@�͂��Ȃ킿�҂ׂ�����
	waitTime = waitTime > 0 ? waitTime : 0;
	return (unsigned)(waitTime);
}
