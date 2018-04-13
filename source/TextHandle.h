#pragma once
#include "DxLib.h"
#include <string>
#include <map>
#include <sstream>
#include "Singleton.h"

class TextHandle : public Singleton<TextHandle>
{
    TextHandle() = default;
    friend Singleton< TextHandle >;
private:
    std::map<std::string, std::string > _fonturl;
    std::map<std::string, int> _fonthandle;
public:
    int setFontUrl(std::string *name, std::string *url);//url‚Í–¼‘O‚Å‚à‚æ‚¢
    int setHandle(std::string *name, int fontsize, int fontthick, int fonttype);
    int setHandle(std::string *filename, std::string *name, int fontsize, int fontthick,int fonttype);

    int getHandle(std::string *name, int fontsize);
    int getHandle(std::string *name, int fontsize, int fontthick, int fonttype);
    int getHandle(std::string *filename);

    void initHandle();
    void removeHandle(std::string *filename);
    ~TextHandle();
};
