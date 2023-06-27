#pragma once

#include "board.h"
#include <string>
#include <vector>

using namespace std;

namespace Notation{
    vector<string> parsePGN(string pgn);
    string moveToPGNMove(Move m, Board *board);
    Move algebraicNotationToMove(string algebraicNotation, int index, Board board);
    vector<Move> pgnToMoves(string pgn, Board *board);
    
    // Import-Export FEN needed to be inside the Board class unfortunately
    bool isValidFEN(string fen);
};