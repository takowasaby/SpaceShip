#pragma once
#include "Task.h"
#include <string>
#include <vector>
#include <memory>
#include "Vector2.h"
//#include "AbstractModule.h"
#include "ObjectCallBackListener.h"

class AbstractModule;

class BoardObject : public Task {	//�퓬��ʗp�I�u�W�F�N�g���N���X
public:
	//��������w�c��\��ID�Q
	const static char* NEUTRAL_CAMP_ID;
	const static char* ENEMY_CAMP_ID;
	const static char* FRIEND_CAMP_ID;
	//

	BoardObject(
		Vector2 center,
		Vector2 velocity,
		int GraphicHandle,
		float direction,
		const char* campID,
		int CanExistTime,
		int manageListNum,
		ObjectCallBackListener* objectCallBackListener
	);

	bool update() override;
	void draw() const override;

	void addModule(std::shared_ptr<AbstractModule> module);

	Vector2 center() const;
	Vector2& center();
	Vector2& velocity();
	Vector2& acceleration();

	float direction() const;
	float& direction();
	int& rotateCount();
	float& goalDirection();

	float radius() const;

	int damage() const;

	void move();
	void rotate();
	bool isRotate();

	void existJudge();

	void depart();

protected:
	std::vector<std::shared_ptr<AbstractModule>> _module;
	ObjectCallBackListener* _objectCallBackListener;
	unsigned int _manageListNum;

	Vector2 _center;		//�I�u�W�F�N�g�̒��S���W
	Vector2 _velocity;		//�I�u�W�F�N�g�̑��x
	Vector2 _acceleration;  //�I�u�W�F�N�g�̉����x

	float _direction;		//�I�u�W�F�N�g�̌���
	int _rotateCount;		//�ړI�̌����ɂ��ǂ蒅���܂ł̎���[flame]
	float _goalDirection;	//�ړI�̌���(���l�ł����Ɖ�])

	float _radius;			//�����蔻��̔��a

	int _damage;			//�Փˎ��̗^�_���[�W

	int _graphicHandle;		//�I�u�W�F�N�g�̉摜�n���h��
	int _graphicSizeX;		//�摜�̉���[pixcel]
	int _graphicSizeY;		//�摜�̏c��[pixcel]

	const char* _campID;			//��������w�c��\��ID

	int _existCount;		//���݂��Ă��鎞��
	int _CanExistTime;		//�퓬��ʏ�ɑ��݂ł���flame�P�ʂ̎��ԁi-1:�����j
};


class AbstractModule
{
protected:
	BoardObject * _obj;
public:

	AbstractModule(BoardObject* obj = nullptr) :
		_obj(obj)
	{
	}
	AbstractModule(const AbstractModule& abs) = delete;
	AbstractModule(const AbstractModule&& abs) = delete;
	AbstractModule&  operator = (const AbstractModule& abs) = delete;

	virtual ~AbstractModule() = default;
	virtual bool update() = 0;
};