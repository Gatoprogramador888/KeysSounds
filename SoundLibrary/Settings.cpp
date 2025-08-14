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
    std::wstring line, retorno;
    while (std::getline(config, line))
    {
        retorno = line;
    }
    return retorno;
}

void Settings::ReadSettings()
{
    configurations.clear();
    std::wifstream config(dirSettings);
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
    std::wofstream archivo(dir + configuration + wextension); // Abre el archivo en modo escritura

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
    if (_wremove((dir + configuration + wextension).c_str()) != 0)
    {
        std::cerr << "The file could not be deleted\n";
    }
    SavedSettings();
}

void Settings::SavedSettings()
{
    std::wofstream config(dirSettings);
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




//Funciones exportar

Settings* Settings_Instance()
{
    return &Settings::Instance();
}

void Settings_Read()
{
    Settings::Instance().ReadSettings();
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
    static std::vector<std::wstring> list = Settings::Instance().Getlist();
    return list.size();
}

MUSIC_API const wchar_t* Settings_PossibleConfigurationAt(size_t index) {
    static std::wstring retorno = Settings::Instance().GetConfiguration(index);
    return retorno.c_str();
}

MUSIC_API void Settings_SaveSettings() {
    Settings::Instance().SavedSettings();
}