#include "WrapperSettings.h"
#include "Editor.h"


WrapperSettings::WrapperSettings(String^ dllPath)
{
    std::wstring path = KeySoundEditor::Editor::SysStringToWString(dllPath);
    hModule = LoadLibrary(path.c_str());
    if (!hModule)
        throw gcnew Exception("No se pudo cargar la DLL");

    pMainConfiguration = (FN_Settings_MainConfiguration)GetProcAddress(hModule, "Settings_MainConfiguration");
    pSetMainConfiguration = (FN_Settings_SetMainConfiguration)GetProcAddress(hModule, "Settings_SetMainConfiguration");
    pAddConfiguration = (FN_Settings_AddConfiguration)GetProcAddress(hModule, "Settings_AddConfiguration");
    pDeleteConfiguration = (FN_Settings_DeleteConfiguration)GetProcAddress(hModule, "Settings_DeleteConfiguration");
    pPossibleConfigurationsCount = (FN_Settings_PossibleConfigurationsCount)GetProcAddress(hModule, "Settings_PossibleConfigurationsCount");
    pPossibleConfigurationAt = (FN_Settings_PossibleConfigurationAt)GetProcAddress(hModule, "Settings_PossibleConfigurationAt");
    pSaveSettings = (FN_Settings_SaveSettings)GetProcAddress(hModule, "Settings_SaveSettings");


    if (!pMainConfiguration || !pSetMainConfiguration || !pAddConfiguration || !pDeleteConfiguration || !pPossibleConfigurationsCount ||
        !pPossibleConfigurationAt || !pSaveSettings)
    {
        FreeLibrary(hModule);
        hModule = nullptr;
        throw gcnew System::Exception("No se pudieron obtener las funciones de LOADMusic en la DLL");
    }
}

WrapperSettings::~WrapperSettings()
{
    if (!hModule) {
        FreeLibrary(hModule);
        hModule = nullptr;
    }
}

String^ WrapperSettings::MainConfiguration()
{
    const wchar_t* result = pMainConfiguration();
    System::String^ retorno = gcnew System::String(result);
    return retorno;
}

void WrapperSettings::SetMainConfiguration(String^ configuration)
{
    std::wstring nativeStr = KeySoundEditor::Editor::SysStringToWString(configuration);
    pSetMainConfiguration(nativeStr);
}

void WrapperSettings::AddConfiguration(String^ configuration)
{
    std::wstring nativeStr = KeySoundEditor::Editor::SysStringToWString(configuration);
    pAddConfiguration(nativeStr);
}

void WrapperSettings::DeleteConfiguration(String^ configuration)
{
    std::wstring nativeStr = KeySoundEditor::Editor::SysStringToWString(configuration);
    pDeleteConfiguration(nativeStr);
}

size_t WrapperSettings::PossibleConfigurationsCount()
{
    return pPossibleConfigurationsCount();
}

String^ WrapperSettings::PossibleConfigurationAt(int index)
{
    const wchar_t* result = pPossibleConfigurationAt(index);
    return gcnew String(result);
}

List<String^>^ WrapperSettings::GetSettings()
{
    List<String^>^ retorno = gcnew List<String^>();
    size_t count = pPossibleConfigurationsCount();

    for (size_t i = 0; i < count; i++)
    {
        retorno->Add(gcnew String(pPossibleConfigurationAt(i)));
    }

    return retorno;
}

void WrapperSettings::SaveSettings()
{
    pSaveSettings();
}
