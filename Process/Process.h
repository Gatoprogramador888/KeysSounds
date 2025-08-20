#pragma once
constexpr const wchar_t* INSTALLER = L"Installer.exe";
constexpr const wchar_t* KEYSOUNDHOOK = L"KeySoundHook.exe";
constexpr const wchar_t* KEYSOUNDEDITOR = L"KeySoundEditor.exe";
class Process
{
private:
	static std::string WcharPToString(const wchar_t* text);
public:
	static void KillProcessByName(const wchar_t* name);
	static void StartProcessByName(const wchar_t* name);
};

