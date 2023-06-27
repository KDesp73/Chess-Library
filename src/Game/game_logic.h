#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "../chess_lib.h"
using namespace std;

namespace Game{
    void start(
        Board *board,
        string interface = Board::CLI
    );
};