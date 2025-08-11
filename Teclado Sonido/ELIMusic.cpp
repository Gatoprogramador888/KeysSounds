#include "ELIMusic.h"

void ELIMusic::Eliminate(int index)
{
    DIR directory;
    try
    {
        directory = listMusic.at((int)index);
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what() << std::endl;
    }
    std::string msgDelete = "Do you want to delete " + SWStringToString(directory.dir) + "?";
    int decision = MessageBox(NULL, msgDelete.c_str(), "Delete ", MB_YESNO | MB_ICONWARNING);

    if (decision == IDNO)return;
    auto objectEliminate = std::find(listMusic.begin(), listMusic.end(), directory);
    if (objectEliminate != listMusic.end()) {
        listMusic.erase(objectEliminate);
    }

    std::string msgIndex = SWStringToString(directory.dir) + " was deleted";
    MessageBox(NULL, msgIndex.c_str(), "", MB_OK | MB_ICONINFORMATION);
}
