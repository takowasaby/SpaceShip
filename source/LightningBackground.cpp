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

//mtrand()で0以上1未満の乱数を返す。
static auto mtrand = getMtRandf();


//valarray用のDrawLineAA
static int DrawLineAAValarray(const valarray<float>& p0, const valarray<float>& p1, unsigned int Color, float Thickness = (1.0F))
{
	return DrawLineAA(p0[0], p0[1], p1[0], p1[1], Color, Thickness);
}

/* Lightningクラスで使う描画設定 */

static const unsigned int Color {GetColor(255, 255, 0)};
static constexpr float Thickness {14.f};
//各方向に進むときの速度ベクトル
static const std::valarray<float> Up_Velocity {100.f, -100.f};
static const std::valarray<float> Right_Velocity {100.f, 0.f};
static const std::valarray<float>  Down_Velocity {100.f, 100.f};

static constexpr float Up_Probabirity {0.f}; //上昇は無い方がきれいだったので、0にした
static constexpr float Down_Probabirity {0.4f};
static constexpr int Turn_Frequency_Frames {5};

//描画する線の長さ(フレーム数)。Turn_Frequency_Frames * 2 以上にすること。
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
	//一定間隔で向きを変える
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

	//TODO: 直線の切れ目が見えてしまう問題に対処する。
	//TODO: これ以下の処理を書き直したい。(初めから初期位置に重ねてhistoryを作っておく？)
	int beforeTail = tailFrame / Turn_Frequency_Frames,
		afterTail = tailFrame / Turn_Frequency_Frames + 1,
		beforeHead = headFrame / Turn_Frequency_Frames;

	//後端
	if (beforeTail >= 0 && afterTail < posHistory.size()) { //描画可能なら
		float weight {static_cast<float>(tailFrame % Turn_Frequency_Frames) / Turn_Frequency_Frames};
		DrawLineAAValarray(posHistory[beforeTail] * (1 - weight) + posHistory[afterTail] * weight, posHistory[afterTail], Color, lineWidth);
	}
	//中央
	for (int i = afterTail; i < beforeHead; i++) {
		if (i >= 0 && i + 1 < posHistory.size()) { //描画可能なら
			DrawLineAAValarray(posHistory[i], posHistory[i + 1], Color, lineWidth);
		}
	}
	//先端
	assert(beforeHead >= 0 && beforeHead < posHistory.size()); //念のため
	DrawLineAAValarray(posHistory[beforeHead], pos, Color, lineWidth);
}

bool Lightning::isAlive() const
{
	//std::maxを括弧で囲んでいるのは、DxLibのmaxマクロの打消しのため
	return pos[0] - (std::max)({Right_Velocity[0], Up_Velocity[0], Down_Velocity[0]}) / z * Tail_Length_Frames <= Define::WIN_W;
}



void LightningBackground::update()
{
	for (const auto& x : lightnings) {
		x->update();
	}
	//左端が画面の右端を超えたら削除
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
	//近くの方が出やすいようにz座標の値を決める
	//遠くの方に出現させると、なかなか消えないから重くなるし、短くてミミズみたいで見た目が良くない
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
