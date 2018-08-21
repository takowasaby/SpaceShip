#pragma once
#include <vector>
#include <valarray>
#include <memory>
#include <string>



//Lightningで使う
enum class LightningDirection {
	Up, Right, Down
};

//LightningBackgroundの要素。
//直線の切れ目が見えるが、高速なら分からなそうなので対処は後回し。
class Lightning {
public:
	constexpr Lightning(float x, float y, float z); // zは画面からの遠さ (z >= 1)
	void update();
	void draw() const;
	bool isAlive() const; //これがfalseを返したらインスタンスを消去する。つまり、auto result = remove_if(lightnings.begin(), lightnings.end(), [](const auto& el) {return !el->isAlive(); }); lightnings.erase(result, lightnings.end());


private:
	//位置ベクトル
	std::valarray<float> pos;
	//線の太さと速度がzに反比例する
	const float z;
	LightningDirection direction;
	//インスタンスが生成されてからのフレーム数
	int headFrame;
	//tailFrame以上のフレームの軌跡を描画
	int tailFrame;
	//Turn_Frequency_Frames間隔で、これに座標をpush_backする
	std::vector<std::valarray<float>> posHistory;


	void randomTurn();
	void move();

};

//背景に折れ曲がる直線のエフェクトを表示させる
class LightningBackground {
public:
	constexpr LightningBackground() = default;
	void update();
	void draw() const;
	void add(); //1本追加する
private:
	std::vector<std::unique_ptr<Lightning>> lightnings {};
};