#include "pch.h"
#include "SAVEMusic.h"
#include "Settings.h"
#include<filesystem>
#include<fstream>

namespace fs = std::filesystem;


std::experimental::generator<std::wstring> SAVEMusic::SavesFile()
{
	fs::path currentPath = fs::current_path();
	std::wstring dirFile = currentPath.wstring() + L"\\Music\\" + Settings::Instance().MainConfiguration() + wextension;
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

