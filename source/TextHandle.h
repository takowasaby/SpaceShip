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
    int setFontUrl(const std::string& name, const std::string& url);//url‚Í–¼‘O‚Å‚à‚æ‚¢
    int setHandle(const std::string& name, int fontsize, int fontthick, int fonttype);
    int setHandle(const std::string& filename, const std::string& name, int fontsize, int fontthick,int fonttype);

    int getHandle(const std::string& name, int fontsize);
    int getHandle(const std::string& name, int fontsize, int fontthick, int fonttype);
    int getHandle(const std::string& filename);

    void initHandle();
    void removeHandle(const std::string& filename);
    ~TextHandle();
};
