#include "pch.h"
#include "Settings.h"
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include<filesystem>

namespace fs = std::filesystem;

Settings& Settings::Instance()
{
    static Settings instance;
    return instance;
}

std::wstring Settings::MainConfiguration()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path currentPath = fs::path(exePath).parent_path();
    std::wstring dir = currentPath / dirMainConfiguration;
    std::wifstream config(dir);
    if (!config.is_open())
    {
        MessageBoxW(NULL, (L"Could not read " + dir).c_str(), L"Error", MB_OK | MB_ICONERROR);
    }
    std::wstring line, retorno;
    while (std::getline(config, line))
    {
        retorno = line;
    }
    return retorno;
}

void Settings::SetCurrentConfiguration(std::wstring configuration)
{
    currentConfiguration = configuration;
}

std::wstring Settings::CurrentConfiguration()
{
    return currentConfiguration;
}

void Settings::ReadSettings()
{
    currentConfiguration = MainConfiguration();
    configurations.clear();
    std::wifstream config(dirSettingsTxt);
    std::wstring line;
    while (std::getline(config, line))
    {
        if(line != L"")  
            configurations.push_back(line);
    }
}

void Settings::SetMainConfiguration(std::wstring configuration)
{
    std::wofstream config(dirMainConfiguration);
    config << configuration;
}

void Settings::AddConfiguration(std::wstring configuration)
{
    configurations.push_back(configuration);
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path dir = fs::path(exePath).parent_path() / (dirMusics + configuration + wextension);
    std::wofstream archivo(dir); // Abre el archivo en modo escritura

    if (archivo.is_open()) {
        std::cout << "Archivo creado exitosamente." << std::endl;
        archivo.close(); // Cierra el archivo
    }
    else {
        std::cerr << "Error al crear el archivo." << std::endl;
    }
    SavedSettings();
}

void Settings::DeleteConfiguration(std::wstring configuration)
{
    auto it = std::find(configurations.begin(), configurations.end() ,configuration);
    configurations.erase(it);
    
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path dir = fs::path(exePath).parent_path() / (dirMusics + configuration + wextension);

    if (_wremove(dir.c_str()) != 0)
    {
        std::cerr << "The file could not be deleted\n";
    }
    SavedSettings();
}

void Settings::SavedSettings()
{
    wchar_t exePath[MAX_PATH];
    GetModuleFileNameW(NULL, exePath, MAX_PATH);
    fs::path dir = fs::path(exePath).parent_path() / dirSettingsTxt;
    std::wofstream config(dir);
    for (size_t i = 0; i < configurations.size(); i++)
    {
        try
        {
            std::wstring configuration = configurations.at(i);
            config << configuration + L"\n";
        }
        catch (const std::out_of_range& oor)
        {
            std::cerr << "Out of Range error: " << oor.what() << std::endl;
        }
    }

    
}

std::wstring Settings::GetConfiguration(size_t index)
{
    try
    {
        std::wstring returns = configurations.at(index);
        return returns;
    }
    catch (const std::out_of_range& oor)
    {
        std::cerr << "Out of Range error: " << oor.what() << std::endl;
    }
    return L"";
}

std::wstring Settings::GetConfigurationAddress()
{
    return dirSettingsMusic + currentConfiguration + wextension;
}

std::wstring Settings::GetMainConfigurationAddress()
{
    return dirSettingsMusic + MainConfiguration() + wextension;
}




//Funciones exportar

Settings* Settings_Instance()
{
    return &Settings::Instance();
}

void Settings_Read()
{
    Settings::Instance().ReadSettings();
}

const wchar_t* Settings_GetCurrentConfiguration()
{
    static std::wstring cache = Settings::Instance().CurrentConfiguration();
    return cache.c_str();
}

void Settings_CurrentConfiguration(std::wstring configuration)
{
    Settings::Instance().SetCurrentConfiguration(configuration);
}

MUSIC_API const wchar_t* Settings_MainConfiguration() {
    static std::wstring recibir = Settings::Instance().MainConfiguration();
    return recibir.c_str();
}

MUSIC_API void Settings_SetMainConfiguration(std::wstring configuration) {
    Settings::Instance().SetMainConfiguration(configuration);
}

MUSIC_API void Settings_AddConfiguration(std::wstring configuration) {
    Settings::Instance().AddConfiguration(configuration);
}

MUSIC_API void Settings_DeleteConfiguration(std::wstring configuration) {
    Settings::Instance().DeleteConfiguration(configuration);
}

MUSIC_API std::size_t Settings_PossibleConfigurationsCount() {
    static std::vector<std::wstring> cache;
    if (cache.empty())
    {
        cache.resize(Settings::Instance().Getlist().size());
    }
    
    return cache.size();
}

MUSIC_API const wchar_t* Settings_PossibleConfigurationAt(size_t index) {
    static std::vector<std::wstring> cache;
    if (cache.empty()) {
        cache.resize(Settings::Instance().Getlist().size());
    }
    cache[index] = Settings::Instance().GetConfiguration(index);
    return cache[index].c_str();
}

MUSIC_API void Settings_SaveSettings() {
    Settings::Instance().SavedSettings();
}