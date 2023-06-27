#include "Pieces.h"
#include "../Board/board_utils.h"

using namespace BoardUtils;

bool Queen::isValidMove(string to, char board[][8]) {
	Coords fromCoords = translateSquare(currentSquare);
	Coords toCoords = translateSquare(to);

	int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x, toCol = toCoords.y;

	int rowDiff = abs(fromRow - toRow);
    int colDiff = abs(fromCol - toCol);

	if(this->capturesOwnPiece(toCoords, board)) return false;

    // Check if the move is valid for the bishop (diagonal movement)
    if (rowDiff == colDiff) {
        int rowStep = (toRow > fromRow) ? 1 : -1;
        int colStep = (toCol > fromCol) ? 1 : -1;
        int i = fromRow + rowStep;
        int j = fromCol + colStep;
        while (i != toRow && j != toCol) {
            if (board[i][j] != ' ') {
                return false;
            }
            i += rowStep;
            j += colStep;
        }
        return true;
    }

    // Check if the move is valid for the rook (horizontal/vertical movement)
    if (fromRow == toRow) {
        int colStep = (toCol > fromCol) ? 1 : -1;
        int j = fromCol + colStep;
        while (j != toCol) {
            if (board[fromRow][j] != ' ') {
                return false;
            }
            j += colStep;
        }
        return true;
    }
    if (fromCol == toCol) {
        int rowStep = (toRow > fromRow) ? 1 : -1;
        int i = fromRow + rowStep;
        while (i != toRow) {
            if (board[i][fromCol] != ' ') {
                return false;
            }
            i += rowStep;
        }
        return true;
    }

    return false;
}

vector<string> Queen::getPseudoValidMoves(char board[][8]){
	char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    vector<string> movesToCheck;
    char tempFile = currentFile;
    int tempRank = currentRank;

    // Check same rank left
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
    tempRank = currentRank;
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

    // Check up and right
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile < 'h' && tempRank < 8){
		tempFile++;
		tempRank++;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
	}

	// Check up and left
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile > 'a' && tempRank < 8){
		tempFile--;
		tempRank++;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
	}

	// Check down and right
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile < 'h' && tempRank > 1){
		tempFile++;
		tempRank--;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
	}

	// Check down and left
	tempFile = currentFile;
	tempRank = currentRank;
	while(tempFile > 'a' && tempRank > 1){
		tempFile--;
		tempRank--;
		movesToCheck.push_back(string(1, tempFile) + to_string(tempRank));
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