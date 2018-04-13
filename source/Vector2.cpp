#include "Vector2.h"
#include <cmath>
#include <cfloat>

//コンストラクタ
Vector2::Vector2(float x, float y) :
	_x(x), _y(y)
{
}


//内積を求める
float Vector2::dot(const Vector2 & other) const
{
	return (_x * other._x) + (_y  * other._y);
}
//外積を求める
float Vector2::cross(const Vector2 & other) const
{
	return (_x * other._y) - (_y * other._x);
}


//ベクトルの長さを求める
float Vector2::length() const
{
	return std::sqrt(dot(*this));
}
//ベクトル間の距離を求める
float Vector2::distance(const Vector2 & other) const
{
	return (*this - other).length();
}


//ベクトルを正規化する（単位ベクトルにするよ！）
Vector2 Vector2::normalize() const
{
	const float len = length();
	if (len < FLT_EPSILON) return Vector2::ZERO;
	return *this / len;
}


//ゼロベクトルかどうかを判定する
bool Vector2::isZero() const
{
	return *this == Vector2::ZERO;
}


//演算子オーバーロード（和、スカラー倍）
Vector2 & Vector2::operator+=(const Vector2 & other)
{
	return *this = *this + other;
}
Vector2 & Vector2::operator-=(const Vector2 & other)
{
	return *this = *this - other;
}
Vector2 & Vector2::operator*=(float scalar)
{
	return *this = *this * scalar;
}
Vector2 & Vector2::operator/=(float scalar)
{
	return *this = *this / scalar;
}


const Vector2 Vector2::operator+(const Vector2 & other) const
{
	return Vector2(_x + other._x, _y + other._y);
}
const Vector2 Vector2::operator-(const Vector2 & other) const
{
	return Vector2(_x - other._x, _y - other._y);
}
const Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(_x * scalar, _y * scalar);
}
const Vector2 Vector2::operator/(float scalar) const
{
	return Vector2(_x / scalar, _y / scalar);
}
//


//ベクトルの反転
const Vector2 Vector2::operator-() const
{
	return Vector2(-_x, -_y);
}


//演算子オーバーロード（論理演算子）
bool Vector2::operator==(const Vector2 & other) const
{
	if (_x != other._x) return false;
	if (_y != other._y) return false;
	return true;
}
bool Vector2::operator!=(const Vector2 & other) const
{
	if (_x != other._x) return true;
	if (_y != other._y) return true;
	return false;
}
bool Vector2::operator<(const Vector2 & other) const
{
	if (_x < other._x) return true;
	if (_y < other._y) return true;
	return false;
}
//


//弧度法の角度を単位ベクトルに変換する
Vector2 Vector2::fromAngle(float radian)
{
	return Vector2(std::cos(radian), std::sin(radian));
}
//ベクトルを弧度法に変換する
float Vector2::toAngle() const
{
	if (isZero()) return 0.0f;
	return std::atan2(_y, _x);
}
//ベクトルを回転する
Vector2 Vector2::rotate(float radian)
{
	return Vector2(
		_x * std::cos(radian) - _y * std::sin(radian),
		_x * std::sin(radian) + _y * std::cos(radian)
	);
}

void Vector2::rotateXaxis()
{
	_y = -_y;
}


bool Vector2::isVertical(const Vector2 & other) const
{
	return dot(other) == 0.0f;
}
bool Vector2::isParallel(const Vector2 & other) const
{
	return cross(other) == 0.0f;
}
bool Vector2::isSharpAngle(const Vector2 & other) const
{
	return !(isVertical(other) || isParallel(other));
}


float Vector2::x() const
{
	return _x;
}
float Vector2::y() const
{
	return _y;
}





//演算子オーバーフロー（スカラー倍）
inline const Vector2 operator * (float scalar, const Vector2& other) {
	return other * scalar;
}


const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::LEFT(-1.0f, 0.0f);
const Vector2 Vector2::RIGHT(1.0f, 0.0f);
const Vector2 Vector2::DOWN(0.0f, -1.0f);
const Vector2 Vector2::UP(0.0f, 1.0f);