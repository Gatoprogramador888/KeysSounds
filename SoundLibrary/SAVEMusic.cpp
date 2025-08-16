#include "pch.h"
#include "SAVEMusic.h"
#include "Settings.h"
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;


std::experimental::generator<std::wstring> SAVEMusic::SavesFile()
{
	wchar_t exePath[MAX_PATH];
	GetModuleFileNameW(NULL, exePath, MAX_PATH);
	fs::path dir = fs::path(exePath).parent_path() / Settings::Instance().GetMainConfigurationAddress();
	std::wofstream fileSave(dir);

	if (!fileSave.is_open())
	{
		MessageBoxW(NULL, (L"Could not read " + dir.wstring()).c_str(), L"Error", MB_OK | MB_ICONERROR);
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

void SAVEMusic::StartAsyncSave()
{
    saveFile = SavesFile();
    genSaveFileIt = saveFile.begin();
    saving = true;
}

void SAVEMusic::UpdateAsyncSave()
{
	if (!saving)
	{
		return;
	}

    if (genSaveFileIt == saveFile.end())
    {
        saving = false;
        saveFile = std::experimental::generator<std::wstring>(); // resetea el generator
        return;
    }

    ++genSaveFileIt;
}

bool SAVEMusic::IsSaveDone() const
{
    return !saving;
}

