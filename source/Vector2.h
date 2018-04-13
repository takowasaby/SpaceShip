#pragma once
class Vector2
{
public:
	Vector2(float x = 0, float y = 0);						//コンストラクタ

	float dot(const Vector2& other) const;					//内積を求める
	float cross(const Vector2& other) const;				//外積を求める

	float length() const;									//ベクトルの長さを求める
	float distance(const Vector2& other) const;				//ベクトル間の距離を求める

	Vector2 normalize() const;								//ベクトルを正規化する（単位ベクトルにするよ！）

	bool isZero() const;									//ゼロベクトルかどうかを判定する

															//演算子オーバーロード（和、スカラー倍）
	Vector2& operator += (const Vector2& other);
	Vector2& operator -= (const Vector2& other);
	Vector2& operator *= (float scalar);
	Vector2& operator /= (float scalar);

	const Vector2 operator + (const Vector2& other) const;
	const Vector2 operator - (const Vector2& other) const;
	const Vector2 operator * (float scalar) const;
	const Vector2 operator / (float scalar) const;
	//

	const Vector2 operator - () const;						//ベクトルの反転

															//演算子オーバーロード（論理演算子）
	bool operator == (const Vector2& other) const;
	bool operator != (const Vector2& other) const;
	bool operator < (const Vector2& other) const;
	//

	static Vector2 fromAngle(float radian);					//弧度法の角度を単位ベクトルに変換する
	float toAngle() const;									//ベクトルを弧度法に変換する
	Vector2 rotate(float radian);							//ベクトルを回転する
	void rotateXaxis();										//X軸を軸に半回転する

	bool isVertical(const Vector2& other) const;
	bool isParallel(const Vector2& other) const;
	bool isSharpAngle(const Vector2& other) const;

	float x() const;
	float y() const;

	const static Vector2 ZERO;		//定数ゼロベクトル
	const static Vector2 LEFT;		//定数単位左向きベクトル
	const static Vector2 RIGHT;		//定数単位右向きベクトル
	const static Vector2 DOWN;		//定数単位下向きベクトル
	const static Vector2 UP;		//定数単位上向きベクトル

private:
	float _x;						//X座標
	float _y;						//Y座標
};

//演算子オーバーフロー（スカラー倍）
inline const Vector2 operator * (float scalar, const Vector2& other);