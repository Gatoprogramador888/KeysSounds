#pragma once
#pragma once
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include <string>
#include <Windows.h>
#include <vector>

struct DIR
{
    std::string dir;
    size_t index = 1;
    bool operator==(const DIR& other) const
    {
        return dir == other.dir && index == other.index;
    }

    DIR& operator=(const DIR& other)
    {
        if (this != &other)
        {
            dir = other.dir;
            index = other.index;
        }
        return *this;
    }
};

extern std::vector<DIR> listMusic;