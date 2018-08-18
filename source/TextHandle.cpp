#include "TextHandle.h"

TextHandle::~TextHandle()
{
}

int TextHandle::setFontUrl(const std::string&  name, const std::string&  url)
{
    _fonturl[name] = url;
    return 0;
}

int TextHandle::setHandle(const std::string&  name, int fontsize = -1, int fontthick = -1, int fonttype = -1)
{
    std::stringstream sstr;
    std::string str;
    sstr << name << "fs:" << fontsize << "ft:" << fontthick << "fy:" << fonttype;
    sstr >> str;
    auto itr = _fonthandle.find(str);
    if (itr != _fonthandle.end())
        return 0;
    int handle;
    handle = CreateFontToHandle(
        _fonturl[name].c_str(),
        fontsize,
        fontthick,
        fonttype
        );
    _fonthandle[name] = handle;
    sstr << name << "fs:" << fontsize;
    sstr >> str;
    _fonthandle[str] = handle;
    sstr.str(""); // バッファをクリアする。
    sstr.clear(std::stringstream::goodbit);
    sstr << name << "fs:" << fontsize << "ft:" << fontthick << "fy:" << fonttype;
    str = "";
    sstr >> str;
    _fonthandle[str] = handle;
    return handle;
}

int TextHandle::setHandle(const std::string&  filename, const std::string&  name, int fontsize, int fontthick, int fonttype)
{
    int handle;
    printfDx("Font Input Name\n%s\n", _fonturl[name].c_str());
    handle = CreateFontToHandle(
        _fonturl[name].c_str(),
        fontsize,
        fontthick,
        fonttype
    );
    _fonthandle[filename] = handle;
    return handle;
}

int TextHandle::getHandle(const std::string&  name, int fontsize)
{
    std::stringstream sstr;
    std::string str;
    sstr << name << "fs:" << fontsize;
    sstr >> str;
    auto itr = _fonthandle.find(str);
    if (itr == _fonthandle.end())
        return -1;
    return _fonthandle[str];
}

int TextHandle::getHandle(const std::string&  name, int fontsize, int fontthick, int fonttype)
{
    std::stringstream sstr;
    std::string str;
    sstr << name << "fs:" << fontsize << "ft:" << fontthick << "fy:" << fonttype;
    sstr >> str;
    auto itr = _fonthandle.find(str);
    if (itr == _fonthandle.end())
        return -1;
    return _fonthandle[str];
}

int TextHandle::getHandle(const std::string&  filename)
{
    auto itr = _fonthandle.find(filename);
    if (itr == _fonthandle.end())
        return -1;
    return _fonthandle[filename];
}

void TextHandle::initHandle()
{
    InitFontToHandle();
}

void TextHandle::removeHandle(const std::string&  filename)
{
    DeleteFontToHandle(_fonthandle[filename]);
    _fonthandle.erase(_fonthandle.find(filename));
}
