#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"
#include <filesystem>
#include <experimental/generator>
#include <fstream>

namespace fs = std::filesystem;

class LOADMusic : public IMusic
{
private:
	LOADMusic() = default;

	std::experimental::generator<std::wstring>loadFile;

	std::experimental::generator<std::wstring> LoadsFile()
	{
		fs::path currentPath = fs::current_path();
		std::string dirFile = currentPath.string() + "\\Music_Directory.txt";
		std::wifstream fileLoad(dirFile);
		size_t index = listMusic.size();

		if (!fileLoad.is_open())
		{
			co_return;
		}

		std::wstring line;

		HWND listBox = GetItem(LB_LMUSIC);

		while (std::getline(fileLoad, line))
		{
			SendMessageW(listBox, LB_ADDSTRING, 0, (LPARAM)line.c_str());
			SendMessageA(listBox, LB_SETITEMDATA, (WPARAM)index, (LPARAM)index);
			DIR directory;
			directory.dir = line;
			directory.index = index;
			listMusic.push_back(directory);
			index = listMusic.size();
			co_yield line;
		}

		fileLoad.close();
	}

	std::experimental::generator<std::wstring>::iterator genLoadFileIt;

public:
	static LOADMusic& Instance()
	{
		static LOADMusic instance;
		return instance;
	}

	void AsyncLoad()
	{
		loadFile = LoadsFile();
		genLoadFileIt = loadFile.begin();
		SetTimer(Dlg, 1, 50, nullptr);
	}

	void AsyncLoadTimer()
	{
		if (genLoadFileIt == loadFile.end())
		{
			KillTimer(Dlg, 1);
			loadFile = std::experimental::generator<std::wstring>();
			return;
		}

		++genLoadFileIt;
	}
	
	LOADMusic(const LOADMusic&) = delete;
	LOADMusic& operator=(const LOADMusic&) = delete;
};

