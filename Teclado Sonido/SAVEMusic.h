#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

class SAVEMusic : public IMusic
{
private:
	SAVEMusic() = default;
public:
	static SAVEMusic& Instance()
	{
		static SAVEMusic instance;
		return instance;
	}

	void Save()
	{
		fs::path currentPath = fs::current_path();
		std::string dirFile = currentPath.string() + "\\Music_Directory.txt";
		std::wofstream fileSave(dirFile);

		if (!fileSave.is_open())
		{
			std::abort();
		}

		for (size_t i = 0; i < listMusic.size(); i++)
		{
			try
			{
				DIR directory = listMusic.at(i);
				fileSave << directory.dir + L"\n";
				std::string msg = "Save " + SWStringToString(std::wstring(directory.dir));
			}
			catch (const std::out_of_range& error)
			{
				std::cerr << error.what() << std::endl;
			}
		}
		fileSave.close();

		MessageBox(NULL, dirFile.c_str(), "Guardado", MB_OK | MB_ICONINFORMATION);
	}

	SAVEMusic(const SAVEMusic&) = delete;
	SAVEMusic& operator=(const SAVEMusic&) = delete;
};

