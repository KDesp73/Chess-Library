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

struct Square{
    std::string name;
    char file = name.at(0);
    int rank = std::stoi(std::to_string(name.at(1)));
    int x = rank -1;
    int y = file - 97;
};