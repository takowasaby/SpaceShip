#include <DxLib.h>
#include <random>
#include <functional>
#include <vector>
#include <valarray>
#include <cassert>
#include <memory>

#include "LightningBackground.h"
#include "Define.h"
using namespace std;



static auto getMtRandf()
{
	random_device rd {};
	mt19937 mt(rd());
	uniform_real_distribution<float> dist {0, 1};
	return bind(dist, mt);
}

//mtrand()��0�ȏ�1�����̗�����Ԃ��B
static auto mtrand = getMtRandf();


//valarray�p��DrawLineAA
static int DrawLineAAValarray(const valarray<float>& p0, const valarray<float>& p1, unsigned int Color, float Thickness = (1.0F))
{
	return DrawLineAA(p0[0], p0[1], p1[0], p1[1], Color, Thickness);
}

/* Lightning�N���X�Ŏg���`��ݒ� */

static const unsigned int Color {GetColor(255, 255, 0)};
static constexpr float Thickness {14.f};
//�e�����ɐi�ނƂ��̑��x�x�N�g��
static const std::valarray<float> Up_Velocity {100.f, -100.f};
static const std::valarray<float> Right_Velocity {100.f, 0.f};
static const std::valarray<float>  Down_Velocity {100.f, 100.f};

static constexpr float Up_Probabirity {0.f}; //�㏸�͖����������ꂢ�������̂ŁA0�ɂ���
static constexpr float Down_Probabirity {0.4f};
static constexpr int Turn_Frequency_Frames {5};

//�`�悷����̒���(�t���[����)�BTurn_Frequency_Frames * 2 �ȏ�ɂ��邱�ƁB
static constexpr int Tail_Length_Frames {70};










constexpr Lightning::Lightning(float x, float y, float z) :
	pos {x, y}, z {z},
	direction {LightningDirection::Right},
	headFrame{-1}, tailFrame{-Tail_Length_Frames - 1},
	posHistory {}
{
}

void Lightning::randomTurn()
{
	const float r {mtrand()};
	if (r < Up_Probabirity) {
		direction = LightningDirection::Up;
	} else if (r < Up_Probabirity + Down_Probabirity) {
		direction = LightningDirection::Down;
	} else {
		direction = LightningDirection::Right;
	}
}

void Lightning::move()
{
	switch (direction) {
	case LightningDirection::Up:
		pos += Up_Velocity / z;
		break;
	case LightningDirection::Right:
		pos += Right_Velocity / z;
		break;
	case LightningDirection::Down:
		pos += Down_Velocity / z;
		break;
	}
}

void Lightning::update()
{
	headFrame++;
	tailFrame++;
	//���Ԋu�Ō�����ς���
	if (headFrame % Turn_Frequency_Frames == 0) {
		randomTurn();
		posHistory.push_back(pos);
	}
	move();

}

void Lightning::draw() const
{
	float lineWidth {Thickness / z};

	assert(posHistory.size() > 0);

	//TODO: �����̐؂�ڂ������Ă��܂����ɑΏ�����B
	//TODO: ����ȉ��̏������������������B(���߂��珉���ʒu�ɏd�˂�history������Ă����H)
	int beforeTail = tailFrame / Turn_Frequency_Frames,
		afterTail = tailFrame / Turn_Frequency_Frames + 1,
		beforeHead = headFrame / Turn_Frequency_Frames;

	//��[
	if (beforeTail >= 0 && afterTail < posHistory.size()) { //�`��\�Ȃ�
		float weight {static_cast<float>(tailFrame % Turn_Frequency_Frames) / Turn_Frequency_Frames};
		DrawLineAAValarray(posHistory[beforeTail] * (1 - weight) + posHistory[afterTail] * weight, posHistory[afterTail], Color, lineWidth);
	}
	//����
	for (int i = afterTail; i < beforeHead; i++) {
		if (i >= 0 && i + 1 < posHistory.size()) { //�`��\�Ȃ�
			DrawLineAAValarray(posHistory[i], posHistory[i + 1], Color, lineWidth);
		}
	}
	//��[
	assert(beforeHead >= 0 && beforeHead < posHistory.size()); //�O�̂���
	DrawLineAAValarray(posHistory[beforeHead], pos, Color, lineWidth);
}

bool Lightning::isAlive() const
{
	//std::max�����ʂň͂�ł���̂́ADxLib��max�}�N���̑ŏ����̂���
	return pos[0] - (std::max)({Right_Velocity[0], Up_Velocity[0], Down_Velocity[0]}) / z * Tail_Length_Frames <= Define::WIN_W;
}



void LightningBackground::update()
{
	for (const auto& x : lightnings) {
		x->update();
	}
	//���[����ʂ̉E�[�𒴂�����폜
	auto result = remove_if(lightnings.begin(), lightnings.end(), [](const auto& el) {return !el->isAlive(); });
	lightnings.erase(result, lightnings.end());
}

void LightningBackground::draw() const
{
	for (const auto& x : lightnings) {
		x->draw();
	}
}

void LightningBackground::add()
{
	//�߂��̕����o�₷���悤��z���W�̒l�����߂�
	//�����̕��ɏo��������ƁA�Ȃ��Ȃ������Ȃ�����d���Ȃ邵�A�Z���ă~�~�Y�݂����Ō����ڂ��ǂ��Ȃ�
	float z;
	if (mtrand() < 0.5) {
		z = mtrand() * 1 + 1;
	} else if (mtrand() < 0.7) {
		z = mtrand() * 5 + 2;
	} else {
		z = mtrand() * 14 + 7;
	}
	lightnings.push_back(make_unique<Lightning>(0.f, (mtrand() * 2 - 1) * Define::WIN_H, z));
}
