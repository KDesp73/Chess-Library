#include <cstdlib>

#include "Pieces.h"
#include "../Board/board_utils.h"

using namespace BoardUtils;

bool Rook::isValidMove(string to, char board[][8]) {
    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x,
        toCol = toCoords.y;

	if(this->capturesOwnPiece(toCoords, board)) return false;

    if (fromRow == toRow) {
        // Moving horizontally
        int step = (toCol > fromCol) ? 1 : -1;
        for (int i = fromCol + step; i != toCol; i += step) {
            if (board[fromRow][i] != ' ') {
                return false;
            }
        }
        return true;
    } else if (fromCol == toCol) {
        // Moving vertically
        int step = (toRow > fromRow) ? 1 : -1;
        for (int i = fromRow + step; i != toRow; i += step) {
            if (board[i][fromCol] != ' ') {
                return false;
            }
        }
        return true;
    }
    return false;
}

vector<string> Rook::getPseudoValidMoves(char board[][8]){
	char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    vector<string> movesToCheck;

    
    // Check same rank left
    char tempFile = currentFile;
    while(tempFile > 'a'){
        tempFile--;
        movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
    }


    // Check same rank right
    tempFile = currentFile;
    while(tempFile < 'h'){
        tempFile++;
        movesToCheck.push_back(string(1, tempFile) + to_string(currentRank));
    }


    // Check same file up
    int tempRank = currentRank;
    while(tempRank < 8){
        tempRank++;
        movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
    }
    
    // Check same file down
    tempRank = currentRank;
    while(tempRank > 1){
        tempRank--;
        movesToCheck.push_back(string(1, currentFile) + to_string(tempRank));
    }

    // Filter invalid moves
    for (int i = 0; i < movesToCheck.size(); i++) {
        if(!this->isValidMove(movesToCheck.at(i), board)){
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    return movesToCheck;
}
