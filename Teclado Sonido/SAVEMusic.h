#pragma once
#include "Header.h"
#include "resource1.h"
#include "IMusic.h"
#include <fstream>
#include <filesystem>
#include <experimental/generator>

namespace fs = std::filesystem;

class SAVEMusic : public IMusic
{
private:
	SAVEMusic() = default;
	bool save = true;

	std::experimental::generator<std::wstring> saveFile;

	std::experimental::generator<std::wstring> SavesFile()
	{
		fs::path currentPath = fs::current_path();
		std::string dirFile = currentPath.string() + "\\Music_Directory.txt";
		std::wofstream fileSave(dirFile);

		if (!fileSave.is_open())
		{
			co_return;
		}

		for (size_t i = 0; i < listMusic.size(); i++)
		{
			try
			{
				DIR directory = listMusic.at(i);
				fileSave << directory.dir + L"\n";

				co_yield directory.dir;
			}
			catch (const std::out_of_range& error)
			{
				std::cerr << error.what() << std::endl;
			}
		}

		fileSave.close();
	}

	std::experimental::generator<std::wstring>::iterator genSaveFileIt;

public:
	static SAVEMusic& Instance()
	{
		static SAVEMusic instance;
		return instance;
	}

	void AsyncSave()
	{
		saveFile = SavesFile();
		genSaveFileIt = saveFile.begin();
		SetTimer(Dlg, 2, 50, nullptr);
		save = true;
		HWND button = GetItem(BTN_SAVE);
		SetWindowText(button, "Save");
		MessageBox(NULL, "Canciones Guardadas correctamente", "Guardado", MB_OK | MB_ICONINFORMATION);
	}


	void AsyncSaveTimer()
	{
		if (genSaveFileIt == saveFile.end())
		{
			KillTimer(Dlg, 2);
			saveFile = std::experimental::generator<std::wstring>();
			return;
		}

		++genSaveFileIt;
	}

	void SetSave()
	{
		save = false;
		HWND button = GetItem(BTN_SAVE);
		SetWindowText(button, "SAVE*");
	}

	SAVEMusic(const SAVEMusic&) = delete;
	SAVEMusic& operator=(const SAVEMusic&) = delete;
};

