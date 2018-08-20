#include "Sound.h"

int Sound::getBgmHandle(const std::string& filename, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1) {
		return -1;
	}
	if (priority == 0 || priority == -1)
	{
		auto itr = _bgm.find(filename);
		if (itr != _bgm.end())
		{
			ChangeVolumeSoundMem(_bgmVolume, _bgm[filename]);
			return _bgm[filename];
		}
	}
	if (priority == 1 || priority == -1)
	{
		auto itr = _priorityBgm.find(filename);
		if (itr != _priorityBgm.end())
		{
			ChangeVolumeSoundMem(_bgmVolume, _priorityBgm[filename]);
			return _priorityBgm[filename];
		}
	}
	return setBgmHandle(filename, priority);
}

int Sound::getBgmHandle(const std::string& filename, float volumeCorrection, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1 && (volumeCorrection < 0 || volumeCorrection > 1)) {
		return -1;
	}
	if (priority == 0 || priority == -1)
	{
		auto itr = _bgm.find(filename);
		if (itr != _bgm.end())
		{
			int ret = _bgm[filename];
			ChangeVolumeSoundMem(static_cast<int>(_bgmVolume * volumeCorrection), ret);
			return ret;
		}
	}
	if (priority == 1 || priority == -1)
	{
		auto itr = _priorityBgm.find(filename);
		if (itr != _priorityBgm.end())
		{
			int ret = _priorityBgm[filename];
			ChangeVolumeSoundMem(static_cast<int>(_bgmVolume * volumeCorrection), ret);
			return ret;
		}
	}
	return setBgmHandle(filename, volumeCorrection, priority);
}

int Sound::setBgmHandle(const std::string& filename, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1) {
		return -1;
	}
	int ret = LoadSoundMem(filename.c_str());
	if (priority == 0 || priority == -1)
		_bgm[filename] = ret;
	else if (priority == 1 || priority == -1)
		_bgm[filename] = ret;
	return ret;
}

int Sound::setBgmHandle(const std::string& filename, const std::string&  url, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1) {
		return -1;
	}
	int ret = LoadSoundMem(url.c_str());
	ChangeVolumeSoundMem(_bgmVolume, ret);
	if (priority == 0 || priority == -1)
		_bgm[filename] = ret;
	else if (priority == 1 || priority == -1)
		_priorityBgm[filename] = ret;
	return ret;
}

int Sound::setBgmHandle(const std::string& filename, float volumeCorrection, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1 && (volumeCorrection < 0 || volumeCorrection > 1)) {
		return -1;
	}
	int ret = LoadSoundMem(filename.c_str());
	ChangeVolumeSoundMem(static_cast<int>(_bgmVolume * volumeCorrection), ret);
	if (priority == 0 || priority == -1)
		_bgm[filename] = ret;
	else if (priority == 1 || priority == -1)
		_priorityBgm[filename] = ret;
	return ret;
}

int Sound::setBgmHandle(const std::string& filename, float volumeCorrection, const std::string&  url, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1 && (volumeCorrection < 0 || volumeCorrection > 1)) {
		return -1;
	}
	int ret = LoadSoundMem(url.c_str());
	ChangeVolumeSoundMem(static_cast<int>(_bgmVolume * volumeCorrection), ret);
	if (priority == 0 || priority == -1)
		_bgm[filename] = ret;
	else if (priority == 1 || priority == -1)
		_priorityBgm[filename] = ret;
	return ret;
}

int Sound::getSeHandle(const std::string& filename, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1) {
		return -1;
	}
	if (priority == 0 || priority == -1)
	{
		auto itr = _se.find(filename);
		if (itr != _se.end())
		{
			return _se[filename];
		}
	}
	if (priority == 1 || priority == -1)
	{
		auto itr = _prioritySe.find(filename);
		if (itr != _prioritySe.end())
		{
			return _prioritySe[filename];
		}
	}
	return setSeHandle(filename, priority);
}

int Sound::getSeHandle(const std::string& filename, float volumeCorrection, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1 && (volumeCorrection < 0 || volumeCorrection > 1)) {
		return -1;
	}
	if (priority == 0 || priority == -1)
	{
		auto itr = _se.find(filename);
		if (itr != _se.end())
		{
			int ret = _se[filename];
			ChangeVolumeSoundMem(static_cast<int>(_seVolume * volumeCorrection), ret);
			return ret;
		}
	}
	if (priority == 1 || priority == -1)
	{
		auto itr = _prioritySe.find(filename);
		if (itr != _prioritySe.end())
		{
			int ret = _prioritySe[filename];
			ChangeVolumeSoundMem(static_cast<int>(_seVolume * volumeCorrection), ret);
			return ret;
		}
	}
	return setSeHandle(filename, volumeCorrection, priority);
}

int Sound::setSeHandle(const std::string& filename, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1) {
		return -1;
	}
	int ret = LoadSoundMem(filename.c_str());
	ChangeVolumeSoundMem(_seVolume, ret);
	if (priority == 0 || priority == -1)
		_se[filename] = ret;
	else if (priority == 1 || priority == -1)
		_se[filename] = ret;
	return ret;
}

int Sound::setSeHandle(const std::string& filename, const std::string&  url, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1) {
		return -1;
	}
	int ret = LoadSoundMem(url.c_str());
	ChangeVolumeSoundMem(_seVolume, ret);
	if (priority == 0 || priority == -1)
		_se[filename] = ret;
	else if (priority == 1 || priority == -1)
		_prioritySe[filename] = ret;
	return ret;
}

int Sound::setSeHandle(const std::string& filename, float volumeCorrection, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1 && (volumeCorrection < 0 || volumeCorrection > 1)) {
		return -1;
	}
	int ret = LoadSoundMem(filename.c_str());
	ChangeVolumeSoundMem(static_cast<int>(_seVolume * volumeCorrection), ret);
	if (priority == 0 || priority == -1)
		_se[filename] = ret;
	else if (priority == 1 || priority == -1)
		_prioritySe[filename] = ret;
	return ret;
}

int Sound::setSeHandle(const std::string& filename, float volumeCorrection, const std::string&  url, int priority)
{
	if (priority != -1 && priority != 0 && priority != 1 && (volumeCorrection < 0 || volumeCorrection > 1)) {
		return -1;
	}
	int ret = LoadSoundMem(url.c_str());
	ChangeVolumeSoundMem(static_cast<int>(_seVolume * volumeCorrection), ret);
	if (priority == 0)
		_se[filename] = ret;
	else if (priority == 1)
		_prioritySe[filename] = ret;
	return ret;
}

void Sound::lightReset()
{
	for (auto itr = _bgm.begin(); itr != _bgm.end(); itr++)
	{
		DeleteSoundMem(itr->second);
	}
	_bgm.clear();
	for (auto itr = _se.begin(); itr != _se.end(); itr++)
	{
		DeleteSoundMem(itr->second);
	}
	_se.clear();
	return;
}

void Sound::reset()
{
	this->lightReset();
	for (auto itr = _priorityBgm.begin(); itr != _priorityBgm.end(); itr++)
	{
		DeleteSoundMem(itr->second);
	}
	_priorityBgm.clear();
	for (auto itr = _prioritySe.begin(); itr != _prioritySe.end(); itr++)
	{
		DeleteSoundMem(itr->second);
	}
	_prioritySe.clear();
	return;
}

bool Sound::setVolume(int bgmVolume, int seVolume)
{
	if (bgmVolume >= 0 && bgmVolume <= 255 && seVolume >= 0 && seVolume <= 255) {
		_bgmVolume = bgmVolume;
		_seVolume = seVolume;
		return true;
	}
	return false;
}
