#include "WrapperDIR.h"
#include <vector>
#include "Editor.h"

bool WrapperDIR::isEmpty()
{
    if (!pGetCount)
        throw gcnew System::Exception("Función pGetCount no está inicializada");
    int count = pGetCount();
    return count <= 1;
}

size_t WrapperDIR::Count()
{
    if (!pGetCount)
        throw gcnew System::Exception("Función pGetCount no está inicializada");
    return pGetCount();
}

void WrapperDIR::AddMusic(System::String^ dir, int index)
{
    std::wstring wdir = KeySoundEditor::Editor::SysStringToWString(dir);
    pAdd(wdir, index);
}

void WrapperDIR::DelMusic(int index)
{
    pDel(index);
}

void WrapperDIR::UpdMusic(int index, DIR_EXPORT* dir)
{
    pUpd(index, dir);
}

DIR_IMPORT^ WrapperDIR::GetMusic(int index)
{
    DIR_EXPORT* dir = pGet(index);
    DIR_IMPORT^ returns = gcnew DIR_IMPORT
    (
        gcnew System::String(dir->dir.c_str()),
        dir->index
    );
    return returns;
}

//System::Collections::Generic::List<System::Tuple<System::String^, int>^>^ WrapperDIR::GetMusicList()
System::Collections::Generic::List<DIR_IMPORT^>^ WrapperDIR::GetMusicList()
{
    size_t count = pGetCount();
    auto list = gcnew System::Collections::Generic::List<DIR_IMPORT^>();
    if (count <= 0) return list;

    std::vector<DIR_EXPORT> buffer(count);
    pGetList(buffer.data(), count);

    for (size_t i = 0; i < count; i++) {
        list->Add(
            gcnew DIR_IMPORT
            (
                gcnew System::String(buffer[i].dir.c_str()),
                buffer[i].index
            )
            );
    }
    return list;
}

void WrapperDIR::SetMusicList(System::Windows::Forms::ListBox::ObjectCollection^ objetos)
{
    std::vector<DIR_EXPORT> dirs;
    for (int i = 0; i < objetos->Count; i++)
    {
        DIR_EXPORT dir;
        dir.dir = KeySoundEditor::Editor::SysStringToWString(objetos[i]->ToString());
        dir.index = i;
        dirs.push_back(dir);
    }

    pSetList(dirs.data(), dirs.size());
    
}

WrapperDIR::WrapperDIR(System::String^ dllPath)
{
    //pin_ptr<const wchar_t> wpath = KeySoundEditor::Editor::SysStringToWString(dllPath).c_str();
    std::wstring wpath = KeySoundEditor::Editor::SysStringToWString(dllPath);
    hDll = LoadLibraryW(wpath.c_str());

    if (!hDll) throw gcnew System::Exception("No se pudo cargar la DLL");

    pGetCount = (fnGetListMusicCount)GetProcAddress(hDll, "GetListMusicCount");
    pGetList = (fnGetListMusic)GetProcAddress(hDll, "GetListMusic");
    pSetList = (fnGetListMusic)GetProcAddress(hDll, "SetListMusic");
    pAdd = (fnAddMusicItem)GetProcAddress(hDll, "AddItem");
    pDel = (fnDeleteMusicItem)GetProcAddress(hDll, "DeleteItem");
    pUpd = (fnModMusicItem)GetProcAddress(hDll, "UpdateItem");
    pGet = (fnGetMusicItem)GetProcAddress(hDll, "GetItem");

    if (!pGetCount || !pGetList || !pSetList || !pAdd || !pDel || !pGet || !pUpd)
        throw gcnew System::Exception("No se encontraron funciones requeridas en la DLL");
}
