#pragma once
#include <string>
#include <Windows.h>
using namespace System;
using namespace System::Collections::Generic;

public ref class WrapperSettings
{
public:
    WrapperSettings(String^ dllPath);
    ~WrapperSettings();

    String^ MainConfiguration();
    void SetMainConfiguration(String^ configuration);
    void AddConfiguration(String^ configuration);
    void DeleteConfiguration(String^ configuration);

    size_t PossibleConfigurationsCount();
    String^ PossibleConfigurationAt(int index);
    List<String^>^ GetSettings();


    void SaveSettings();

private:
    HMODULE hModule;

    // Punteros a las funciones de la DLL
    // Tipos de función que coinciden EXACTAMENTE con la DLL
    typedef const wchar_t* (*FN_Settings_MainConfiguration)();
    typedef void (*FN_Settings_SetMainConfiguration)(std::wstring);
    typedef void (*FN_Settings_AddConfiguration)(std::wstring);
    typedef void (*FN_Settings_DeleteConfiguration)(std::wstring);
    typedef size_t(*FN_Settings_PossibleConfigurationsCount)();
    typedef const wchar_t* (*FN_Settings_PossibleConfigurationAt)(size_t);
    typedef void (*FN_Settings_SaveSettings)();
    typedef void (*FN_Settings_ReadSettings)();

    // Punteros a las funciones
    FN_Settings_MainConfiguration pMainConfiguration;
    FN_Settings_SetMainConfiguration pSetMainConfiguration;
    FN_Settings_AddConfiguration pAddConfiguration;
    FN_Settings_DeleteConfiguration pDeleteConfiguration;
    FN_Settings_PossibleConfigurationsCount pPossibleConfigurationsCount;
    FN_Settings_PossibleConfigurationAt pPossibleConfigurationAt;
    FN_Settings_SaveSettings pSaveSettings;
    FN_Settings_ReadSettings pReadSettings;
};

