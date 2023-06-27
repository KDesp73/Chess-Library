#include <cstdlib>

#include "../Board/board_utils.h"
#include "Pieces.h"

using namespace BoardUtils;

bool Pawn::isValidMove(string to, char board[][8]) {
    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x,
        toCol = toCoords.y;

    int direction;
    if (this->color == "white") {
        direction = 1;
    } else {
        direction = -1;
    }

    // Check if the pawn is moving forward one or two squares
    if (toCol == fromCol && toRow == fromRow + direction) {
        if (board[toRow][toCol] == ' ') {
            return true;
        }
    } else if (toCol == fromCol && toRow == fromRow + 2 * direction &&
               fromRow == (this->color == "white" ? 1 : 6)) {
        if (board[toRow][toCol] == ' ' &&
            board[fromRow + direction][toCol] == ' ') {
            return true;
        }
    }
    // Check if the pawn is capturing an opponent's piece
    bool isOpponentsPiece =
        ((this->color == "white" && !isupper(board[toRow][toCol])) ||
         (this->color == "black" && isupper(board[toRow][toCol])));
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol] != ' ' && isOpponentsPiece) {
            return true;
        }
    }
    return false;
}

bool Pawn::isValidCapture(string to, char board[][8]) {
    int direction;
    if (this->color == "white") {
        direction = 1;
    } else {
        direction = -1;
    }

    Coords fromCoords = translateSquare(currentSquare);
    Coords toCoords = translateSquare(to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y, toRow = toCoords.x,
        toCol = toCoords.y;

    if (this->capturesOwnPiece(toCoords, board)) return false;

    // Check if the pawn is capturing an opponent's piece
    bool isOpponentsPiece =
        ((this->color == "white" && !isupper(board[toRow][toCol])) ||
         (this->color == "black" && isupper(board[toRow][toCol])));
    if (abs(toCol - fromCol) == 1 && toRow == fromRow + direction) {
        if (board[toRow][toCol] != ' ' && isOpponentsPiece) {
            return true;
        }
    }
    return false;
}

bool Pawn::attacksSquare(string square, char board[][8]){
    char currentFile = this->currentSquare.at(0);
    int currentRank = this->currentSquare.at(1) - 48;

    int direction = (color == Piece::WHITE) ? 1 : -1;

    vector<string> capturesToCheck = {
        string(1, currentFile + 1) + to_string(currentRank + direction),
        string(1, currentFile - 1) + to_string(currentRank + direction),
    };

    // Filter invalid squares
    for (int i = 0; i < capturesToCheck.size(); i++) {
        if (!isValidSquare(capturesToCheck.at(i))) {
            capturesToCheck.erase(capturesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    for (int i = 0; i < capturesToCheck.size(); i++){
        if(square == capturesToCheck.at(i)) return true;
    }

    return false;
}

bool Pawn::canPromote(string to, char board[][8]){
    bool validMove = this->isValidMove(to, board);
    bool validCapture = this->isValidCapture(to, board);
    if(this->color == "white"){
        return (validMove || validCapture) && translateSquare(to).x == 7;
    } else {
        return (this->isValidMove(to, board) || this->isValidCapture(to, board)) && translateSquare(to).x == 0;
    } 
}

vector<string> Pawn::getPseudoValidMoves(char board[][8]) {
    char currentFile = currentSquare.at(0);
    int currentRank = currentSquare.at(1) - 48;

    int direction = (color == Piece::WHITE) ? 1 : -1;

    vector<string> movesToCheck = {
        string(1, currentFile) + to_string(currentRank + 1 * direction),
        string(1, currentFile) + to_string(currentRank + 2 * direction)};
    vector<string> capturesToCheck = {
        string(1, currentFile + 1) + to_string(currentRank + 1 * direction),
        string(1, currentFile - 1) + to_string(currentRank + 1 * direction),
    };

    // Filter invalid moves
    for (int i = 0; i < movesToCheck.size(); i++) {
        if (!this->isValidMove(movesToCheck.at(i), board)) {
            movesToCheck.erase(movesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    // Filter invalid captures
    for (int i = 0; i < capturesToCheck.size(); i++) {
        if (!this->isValidCapture(capturesToCheck.at(i), board)) {
            capturesToCheck.erase(capturesToCheck.begin() + i);  // erase from vector
            i--;
        }
    }

    // Manually concat the two vectors
    for(string capture : capturesToCheck){
		movesToCheck.push_back(capture);
	}

	return movesToCheck;
}

bool Pawn::canEnpassant(string to, Move move_1_before){
    char currentFile = this->currentSquare.at(0);
    int currentRank = this->currentSquare.at(1) - 48;

    int rankToEnpassant = (color == Piece::WHITE) ? 5 : 4;
    int direction = (color == Piece::WHITE) ? 1 : -1;

    if(currentRank != rankToEnpassant) return false;

    int right  = (color == Piece::WHITE) ? 1 : -1;
    int left  = (color == Piece::WHITE) ? -1 : 1;

    string square_right = string(1, currentFile + right) + to_string(currentRank);
    string square_left = string(1, currentFile + left) + to_string(currentRank);


    Move move_right;
    Move move_left;

    if(isValidSquare(square_left)){
        move_left = {string(1, currentFile + left) + to_string(currentRank - 2 * (-direction)), square_left};
    }

    if(isValidSquare(square_right)){
        move_right = {string(1, currentFile + right) + to_string(currentRank - 2 * (-direction)), square_right};
    }

    if(move_1_before.from == move_left.from && move_1_before.to == move_left.to){
        string squareToGo = string(1, currentFile + left) + to_string(currentRank + direction);
        if(to == squareToGo) return true;
    }

    if(move_1_before.from == move_right.from && move_1_before.to == move_right.to){
        string squareToGo = string(1, currentFile + right) + to_string(currentRank + direction);
        if(to == squareToGo) return true;
    }

    return false;
}