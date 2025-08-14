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
    fs::path currentPath = fs::current_path();
    std::wstring dir = currentPath.wstring() + L"\\" + dirMainConfiguration;
    std::wifstream config(dir);
    //MessageBoxW(NULL, dir.c_str(), L"", MB_OK);
    std::wstring line, retorno;
    while (std::getline(config, line))
    {
        retorno = line;
        //MessageBoxW(NULL, line.c_str(), L"", MB_OK);
    }
    return retorno;
}

std::vector<std::wstring> Settings::PossibleConfigurations()
{
    std::wifstream config(dirSettings);
    std::wstring line;
    while (std::getline(config, line))
    {
        if(line != L"")  
            configurations.push_back(line);
    }
    return configurations;
}

void Settings::SetMainConfiguration(std::wstring configuration)
{
    std::wofstream config(dirMainConfiguration);
    config << configuration;
}

void Settings::AddConfiguration(std::wstring configuration)
{
    configurations.push_back(configuration);
    std::wofstream archivo(dir + configuration); // Abre el archivo en modo escritura

    if (archivo.is_open()) {
        std::cout << "Archivo creado exitosamente." << std::endl;
        archivo.close(); // Cierra el archivo
    }
    else {
        std::cerr << "Error al crear el archivo." << std::endl;
    }
}

void Settings::DeleteConfiguration(std::wstring configuration)
{
    auto it = std::find(configurations.begin(), configurations.end() ,configuration);
    configurations.erase(it);
    if (_wremove((dir + configuration).c_str()) != 0)
    {
        std::cerr << "The file could not be deleted\n";
    }
}

void Settings::SavedSettings()
{
    std::wofstream config(dirSettings);
    config << MainConfiguration() + L"\n";
    for (size_t i = 0; i < configurations.size(); i++)
    {
        try
        {
            config << configurations.at(i) + L"\n";
        }
        catch (const std::out_of_range& oor)
        {
            std::cerr << "Out of Range error: " << oor.what() << std::endl;
        }
    }
}




//Funciones exportar

Settings* Settings_Instance()
{
    return &Settings::Instance();
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
    return Settings::Instance().PossibleConfigurations().size();
}

MUSIC_API const wchar_t* Settings_PossibleConfigurationAt(size_t index) {
    static std::wstring retorno = Settings::Instance().GetConfiguration(index);
    return retorno.c_str();
}

MUSIC_API void Settings_SaveSettings() {
    Settings::Instance().SavedSettings();
}