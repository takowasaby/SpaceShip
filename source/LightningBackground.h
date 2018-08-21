#pragma once
#include <vector>
#include <valarray>
#include <memory>
#include <string>



//Lightning�Ŏg��
enum class LightningDirection {
	Up, Right, Down
};

//LightningBackground�̗v�f�B
//�����̐؂�ڂ������邪�A�����Ȃ番����Ȃ����Ȃ̂őΏ��͌�񂵁B
class Lightning {
public:
	constexpr Lightning(float x, float y, float z); // z�͉�ʂ���̉��� (z >= 1)
	void update();
	void draw() const;
	bool isAlive() const; //���ꂪfalse��Ԃ�����C���X�^���X����������B�܂�Aauto result = remove_if(lightnings.begin(), lightnings.end(), [](const auto& el) {return !el->isAlive(); }); lightnings.erase(result, lightnings.end());


private:
	//�ʒu�x�N�g��
	std::valarray<float> pos;
	//���̑����Ƒ��x��z�ɔ���Ⴗ��
	const float z;
	LightningDirection direction;
	//�C���X�^���X����������Ă���̃t���[����
	int headFrame;
	//tailFrame�ȏ�̃t���[���̋O�Ղ�`��
	int tailFrame;
	//Turn_Frequency_Frames�Ԋu�ŁA����ɍ��W��push_back����
	std::vector<std::valarray<float>> posHistory;


	void randomTurn();
	void move();

};

//�w�i�ɐ܂�Ȃ��钼���̃G�t�F�N�g��\��������
class LightningBackground {
public:
	constexpr LightningBackground() = default;
	void update();
	void draw() const;
	void add(); //1�{�ǉ�����
private:
	std::vector<std::unique_ptr<Lightning>> lightnings {};
};