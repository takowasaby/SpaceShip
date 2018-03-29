#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include "Singleton.h"

class Graphics : public Singleton<Graphics> 
{
	Graphics() = default;
	friend Singleton< Graphics >;

	//このクラスでは、名前をStringで渡すとそれに合ったハンドルIDを変換します。
	//仮にその名前のデータが含まれていなければ、新たにロードし、あればすでにあるハンドルを渡す。
private:
	std::map<std::string, int> _graphics;//シーン遷移ごとに消去されることが前提
	std::map<std::string, int> _priorityGraphics;//全体が終わるまでは消されないことが前提
	int _debug;
public:
	int getHandle(std::string *filename);
	int getHandle(std::string *filename, int priority);

	int setHandle(std::string *filename);
	int setHandle(std::string *filename, int priority);
	int setHandle(std::string *filename, std::string *url);
	int setHandle(std::string *filename, std::string *url, int priority);

	void getSize(int *graphicSizeX, int *graphicSizeY, int handele);
	void lightReset();//重要度の低いものだけリセットする(priority = 0)
	void reset();//すべてのデータを消去する
};
