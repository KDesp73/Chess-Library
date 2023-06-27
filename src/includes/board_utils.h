#pragma once

#include <vector>
#include <string>

using namespace std;

#include "structs.h"
#include "pieces.h"
#include "board.h"

namespace BoardUtils{
    bool contains(vector<string> moves, string move);
    bool makeMove(string from, string to, char board[][8]); // The primitive one

    int calcDirection(King *king, string square);
    
    void printCoords(Coords coords);
    void printCoords(string square);
    void emptyBoard(char board[][8]);
    
    char pieceToMove(Coords coords, char board[][8]);
    char pieceToMove(string square, char board[][8]);
    
    Coords translateSquare(string square);
    string translateSquare(Coords coords);
    vector<Piece*> squareIsAttacked(string square, Pieces *p, char board[][8]);
    Rook* getRookToCastle(int direction, string color, Board *board);
    string offsetSquare(string square, int offset_v, int offset_h);


    void addSpaces(int row, int starting, int numberOfSpaces, char board[][8]); // not used

    string addSpaces(int index, int num, string fen); 

    string replaceSpaces(string fen);

    std::vector<std::string> splitString(const std::string& input, char delimiter);

    int findMove(Move move, vector<Move> moves);

    bool isValidSquare(string square);

    int characterQuantity(char c, string str);
}