#include "SoundSystem.h"

std::wstring Sound::RandomSound()
{
        DIR directory;
        if (listMusic.empty()) return L"";

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, static_cast<int>(listMusic.size() - 1));

        int randomNumber = dis(gen);
        try
        {
            directory = listMusic.at(randomNumber);
        }
        catch (std::out_of_range error)
        {
            directory = listMusic.at(0);
        }
        return directory.dir;
}
