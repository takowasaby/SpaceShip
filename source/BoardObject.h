#pragma once
#include "Task.h"
#include <string>
#include <vector>
#include <memory>
#include "Vector2.h"
//#include "AbstractModule.h"
#include "ObjectCallBackListener.h"

class AbstractModule;

class BoardObject : public Task {	//戦闘画面用オブジェクト基底クラス
public:
	//所属する陣営を表すID群
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

	Vector2 _center;		//オブジェクトの中心座標
	Vector2 _velocity;		//オブジェクトの速度
	Vector2 _acceleration;  //オブジェクトの加速度

	float _direction;		//オブジェクトの向き
	int _rotateCount;		//目的の向きにたどり着くまでの時間[flame]
	float _goalDirection;	//目的の向き(負値でずっと回転)

	float _radius;			//あたり判定の半径

	int _damage;			//衝突時の与ダメージ

	int _graphicHandle;		//オブジェクトの画像ハンドル
	int _graphicSizeX;		//画像の横幅[pixcel]
	int _graphicSizeY;		//画像の縦幅[pixcel]

	const char* _campID;			//所属する陣営を表すID

	int _existCount;		//存在している時間
	int _CanExistTime;		//戦闘画面上に存在できるflame単位の時間（-1:無限）
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