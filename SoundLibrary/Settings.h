#pragma once
#include "Header.h"
#include <Windows.h>
#include <string>

constexpr const wchar_t* wextension = L".txt";
constexpr const char* extension = ".txt";

class MUSIC_API Settings
{
private:
	Settings() = default;
	std::vector<std::wstring> configurations;
	const std::wstring dirConfig = L"..\\config\\";
	const std::wstring dirSettings = dirConfig + L"settings\\";
	const std::wstring dirSettingsMusic = dirConfig + L"music\\";
	const std::wstring dirMainConfiguration = dirSettings + L"MainConfiguration.txt"; 
	const std::wstring dirSettingsTxt = dirSettings + L"Settings.txt";          
	const std::wstring dirMusicDirectory = dirSettingsMusic + L"Music_Directory.txt";     
	const std::wstring dirMusics = L"..\\assets\\music\\";
	std::wstring currentConfiguration = L"";
public:
	static Settings& Instance();
	Settings(const Settings&) = delete;
	Settings& operator=(const Settings&) = delete;

	std::wstring MainConfiguration();

	void SetCurrentConfiguration(std::wstring configuration);

	std::wstring CurrentConfiguration();

	void ReadSettings();

	void SetMainConfiguration(std::wstring configuration);

	void AddConfiguration(std::wstring configuration);

	void DeleteConfiguration(std::wstring configuration);

	void SavedSettings();

	std::wstring GetConfiguration(size_t index);

	std::vector<std::wstring> Getlist() { return configurations; }

	std::wstring GetConfigurationAddress();

	std::wstring GetMainConfigurationAddress();

};


// Funciones tipo C que actúan como puente
extern "C" {
	MUSIC_API Settings* Settings_Instance();

	MUSIC_API void Settings_Read();
	MUSIC_API const wchar_t* Settings_GetCurrentConfiguration();
	MUSIC_API void Settings_CurrentConfiguration(std::wstring configuration);

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