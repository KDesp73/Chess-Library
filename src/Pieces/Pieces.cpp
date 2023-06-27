#include "Pieces.h"
#include "../Board/board_utils.h"

using namespace BoardUtils;

#include <cctype>

const string Piece::WHITE = "white";
const string Piece::BLACK = "black";

const string Piece::KING = "King";
const string Piece::QUEEN = "Queen";
const string Piece::ROOK = "Rook";
const string Piece::BISHOP = "Bishop";
const string Piece::KNIGHT = "Knight";
const string Piece::PAWN = "Pawn";

const int Pieces::starting_material = 39;


void Pieces::printPieces(){
	for(int i=0; i< pieces.size(); i++){	
		pieces.at(i)->printPiece();
	}
	cout << endl;
}

Piece* Pieces::pieceInSquare(string square, char board[][8]){
	for(int i=0; i < pieces.size(); i++){
		if(pieces.at(i)->currentSquare == square) return pieces.at(i);
	}
	return NULL;
}

int Pieces::calculateMaterial(){
	if(pieces.size() == 0) return -1;

	int material = 0;
	for (int i = 0; i < pieces.size(); i++){
		if(pieces.at(i)->type == Piece::KING) continue;
		material += pieces.at(i)->value;
	}

	this->material = material;
	return material;
}

Piece* pieceFromChar(int x, int y, char board[][8]){
	switch(board[x][y]){
		case 'p':
			return new Pawn(translateSquare(Coords{x, y}), "black");
			break;
		case 'P':
			return new Pawn(translateSquare(Coords{x, y}), "white");
			break;
		case 'r':
			return new Rook(translateSquare(Coords{x, y}), "black");
			break;
		case 'R':
			return new Rook(translateSquare(Coords{x, y}), "white");
			break;
		case 'n':
			return new Knight(translateSquare(Coords{x, y}), "black");
			break;
		case 'N':
			return new Knight(translateSquare(Coords{x, y}), "white");
			break;
		case 'b':
			return new Bishop(translateSquare(Coords{x, y}), "black");
			break;
		case 'B':
			return new Bishop(translateSquare(Coords{x, y}), "white");
			break;
		case 'q':
			return new Queen(translateSquare(Coords{x, y}), "black");
			break;
		case 'Q':
			return new Queen(translateSquare(Coords{x, y}), "white");
			break;
		case 'k':
			return new King(translateSquare(Coords{x, y}), "black");
			break;
		case 'K':
			return new King(translateSquare(Coords{x, y}), "white");
			break;
		default:
			return NULL;
	}
}

void WhitePieces::loadPieces(char board[][8]){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(board[i][j] != ' ' && isupper(board[i][j]))
				this->pieces.push_back(pieceFromChar(i, j, board));
		}
		
	}
}

void BlackPieces::loadPieces(char board[][8]){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if(board[i][j] != ' ' && !isupper(board[i][j]))
				this->pieces.push_back(pieceFromChar(i, j, board));
		}
		
	}
	
}

vector<Piece *> Pieces::isValidMove(string square, char board[][8]){
	vector<Piece *> ret;
	for (int i = 0; i < this->pieces.size(); i++){
		if(this->pieces.at(i)->isValidMove(square, board)) ret.push_back(this->pieces.at(i));
		if(dynamic_cast<Pawn *>(this->pieces.at(i)) != NULL && dynamic_cast<Pawn *>(this->pieces.at(i))->isValidCapture(square, board)) ret.push_back(this->pieces.at(i));
	}
	
	return ret;
}