#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"

class LOADMusic : public IMusic
{
private:
	LOADMusic() = default;
public:
	static LOADMusic& Instance()
	{
		static LOADMusic instance;
		return instance;
	}
	void Load()
	{

	}
	LOADMusic(const LOADMusic&) = delete;
	LOADMusic& operator=(const LOADMusic&) = delete;
};

