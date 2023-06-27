#pragma once

#include <string>
#include <stdio.h>
#include <cstring>


struct Move{
    std::string from;
    std::string to;
    std::string promotion;
};

struct Coords{
    int x;
    int y;
};