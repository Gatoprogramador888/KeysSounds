#include "MODMusic.h"

DIR MODMusic::Modify(int index)
{
    try
    {
        DIR directory = listMusic.at((int)index);
        std::string msgModify = "Do you want to modify " + SWStringToString(directory.dir) + "?";
        int decision = MessageBox(NULL, msgModify.c_str(), "Modify", MB_YESNO | MB_ICONWARNING);

        if (decision == IDNO)return DIR();

        std::wstring wfile = OpenFileDialog();
        if (wfile.empty()) {
            std::cout << "Diálogo cancelado o error." << std::endl;
            return DIR();
        }

        directory.dir = wfile;
        listMusic.at(index) = directory;

        std::string msg = "Modifies " + SWStringToString(wfile);
        MessageBox(NULL, msg.c_str(), "", MB_OK | MB_ICONINFORMATION);
        return directory;
    }
    catch (const std::out_of_range& error)
    {
        std::cerr << error.what() << std::endl;
    }
    return DIR();
}
