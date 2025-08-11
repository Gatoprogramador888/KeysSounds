#include "ADDMusic.h"

DIR ADDMusic::Add()
{
    std::wstring wfile = OpenFileDialog();
    if (wfile.empty()) {
        std::cout << "Diálogo cancelado o error." << std::endl;
        return DIR();
    }

    index = listMusic.size();
    DIR directory = { wfile, index };
    listMusic.push_back(directory);

    std::string msg = "Added " + SWStringToString(wfile) + " with index:" + std::to_string(index);
    MessageBox(NULL, msg.c_str(), "", MB_OK | MB_ICONINFORMATION);

    return directory;
}
