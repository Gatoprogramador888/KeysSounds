#pragma once
#include "Header.h"
#include <Windows.h>
#include <string>

class MUSIC_API Settings
{
private:
	Settings() = default;
	std::vector<std::wstring> configurations;
	std::wstring dirMainConfiguration = L"Settings\\MainCofiguration.txt", dirSettings = L"Settings\\Settings.txt", dir = L"Music\\";
public:
	static Settings& Instance();
	Settings(const Settings&) = delete;
	Settings& operator=(const Settings&) = delete;

	std::wstring MainConfiguration();

	std::vector<std::wstring> PossibleConfigurations();

	void SetMainConfiguration(std::wstring configuration);

	void AddConfiguration(std::wstring configuration);

	void DeleteConfiguration(std::wstring configuration);

	void SavedSettings();

	std::wstring GetConfiguration(size_t index)
	{
		try
		{
			return configurations.at(index);
		}
		catch (const std::out_of_range& oor)
		{
			std::cerr << "Out of Range error: " << oor.what() << std::endl;
		}
		return L"";
	}

};


// Funciones tipo C que actúan como puente
extern "C" {
	MUSIC_API Settings* Settings_Instance();

	MUSIC_API const wchar_t* Settings_MainConfiguration();
	MUSIC_API void Settings_SetMainConfiguration(std::wstring configuration);
	MUSIC_API void Settings_AddConfiguration(std::wstring configuration);
	MUSIC_API void Settings_DeleteConfiguration(std::wstring configuration);

	// Devolver array dinámico de configuraciones
	MUSIC_API size_t Settings_PossibleConfigurationsCount();
	MUSIC_API const wchar_t* Settings_PossibleConfigurationAt(size_t index);

	// Guardar ajustes
	MUSIC_API void Settings_SaveSettings();
}