#pragma once
class Vector2
{
public:
	Vector2(float x = 0, float y = 0);						//�R���X�g���N�^

	float dot(const Vector2& other) const;					//���ς����߂�
	float cross(const Vector2& other) const;				//�O�ς����߂�

	float length() const;									//�x�N�g���̒��������߂�
	float distance(const Vector2& other) const;				//�x�N�g���Ԃ̋��������߂�

	Vector2 normalize() const;								//�x�N�g���𐳋K������i�P�ʃx�N�g���ɂ����I�j

	bool isZero() const;									//�[���x�N�g�����ǂ����𔻒肷��

															//���Z�q�I�[�o�[���[�h�i�a�A�X�J���[�{�j
	Vector2& operator += (const Vector2& other);
	Vector2& operator -= (const Vector2& other);
	Vector2& operator *= (float scalar);
	Vector2& operator /= (float scalar);

	const Vector2 operator + (const Vector2& other) const;
	const Vector2 operator - (const Vector2& other) const;
	const Vector2 operator * (float scalar) const;
	const Vector2 operator / (float scalar) const;
	//

	const Vector2 operator - () const;						//�x�N�g���̔��]

															//���Z�q�I�[�o�[���[�h�i�_�����Z�q�j
	bool operator == (const Vector2& other) const;
	bool operator != (const Vector2& other) const;
	bool operator < (const Vector2& other) const;
	//

	static Vector2 fromAngle(float radian);					//�ʓx�@�̊p�x��P�ʃx�N�g���ɕϊ�����
	float toAngle() const;									//�x�N�g�����ʓx�@�ɕϊ�����
	Vector2 rotate(float radian);							//�x�N�g������]����
	void rotateXaxis();										//X�������ɔ���]����

	bool isVertical(const Vector2& other) const;
	bool isParallel(const Vector2& other) const;
	bool isSharpAngle(const Vector2& other) const;

	float x() const;
	float y() const;

	const static Vector2 ZERO;		//�萔�[���x�N�g��
	const static Vector2 LEFT;		//�萔�P�ʍ������x�N�g��
	const static Vector2 RIGHT;		//�萔�P�ʉE�����x�N�g��
	const static Vector2 DOWN;		//�萔�P�ʉ������x�N�g��
	const static Vector2 UP;		//�萔�P�ʏ�����x�N�g��

private:
	float _x;						//X���W
	float _y;						//Y���W
};

//���Z�q�I�[�o�[�t���[�i�X�J���[�{�j
inline const Vector2 operator * (float scalar, const Vector2& other);