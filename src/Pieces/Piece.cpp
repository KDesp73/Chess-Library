#include "Pieces.h"
#include "../Board/board_utils.h"

using namespace BoardUtils;

void Piece::printPiece(){
	cout << this->toString() << endl;
}

string Piece::toString(){
	return this->type + " " + this->color + " " + this->currentSquare;
}

bool Piece::capturesOwnPiece(Coords toCoords, char board[][8]){
	return (isupper(board[toCoords.x][toCoords.y]) && this->color == WHITE) || (islower(board[toCoords.x][toCoords.y]) && this->color == BLACK);
}

