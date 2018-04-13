#pragma once
#include <windef.h>

class BitUtils {
public:
	BitUtils() = delete;

	static DWORD BitSeparate32(DWORD n);
};