#pragma once

#include <iostream>
#include <vector>
#include "../Board/structs.h"
#include "../GUI/Rendering/rendering.h"

using namespace std;

class Piece {
	public:
		static const string WHITE;
		static const string BLACK;

		static const string KING;
		static const string QUEEN;
		static const string ROOK;
		static const string BISHOP;
		static const string KNIGHT;
		static const string PAWN;

		Image image;
		string currentSquare;
		string color;
		char boardChar;
		int value;
		string type;
		bool hasMoved = false;
		
		virtual ~Piece(){
		}
		
		Piece(){
		}	
		
		Piece(string currentSquare, string color){
			if(color != WHITE && color != BLACK){
				cout << "Incorrect color" << endl;
			}
			
			this->currentSquare = currentSquare;
			this->color = color;
		}
		virtual void printPiece();
		virtual string toString();
		virtual bool isValidMove(string to, char board[][8]){return false;}
		virtual vector<string> getPseudoValidMoves(char board[][8]){vector<string> ret; return ret;}
		bool capturesOwnPiece(Coords toCoords, char board[][8]);
};

class Pawn: public Piece {
	public:
		Pawn(string currentSquare, string color) : Piece(currentSquare, color){
			value = 1;
			this->type = PAWN;
			if(color == WHITE){
				this->boardChar = 'P';
			} else {
				this->boardChar = 'p';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getPseudoValidMoves(char board[][8]) override;
		bool isValidCapture(string to, char board[][8]);
		bool canPromote(string to, char board[][8]);
		bool attacksSquare(string square, char board[][8]);
		bool canEnpassant(string to, Move move_1_before);
};


class Rook: public Piece {
	public:
		Rook(string currentSquare, string color) : Piece(currentSquare, color) {
			this->type = ROOK;
			value = 5;
			if(color == WHITE){
				this->boardChar = 'R';
			} else {
				this->boardChar = 'r';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getPseudoValidMoves(char board[][8]) override;
};

class Knight: public Piece {
	public:
		Knight(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			this->type = KNIGHT;
			if(color == WHITE){
				this->boardChar = 'N';
			} else {
				this->boardChar = 'n';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getPseudoValidMoves(char board[][8]) override;
};

class Bishop: public Piece {
	public:
		Bishop(string currentSquare, string color) : Piece(currentSquare, color){
			value = 3;
			this->type = BISHOP;
			if(color == WHITE){
				this->boardChar = 'B';
			} else {
				this->boardChar = 'b';
			}
		}
		vector<string> getPseudoValidMoves(char board[][8]) override;
		bool isValidMove(string to, char board[][8]) override;
};

class Queen: public Piece {
	public:
		Queen(string currentSquare, string color) : Piece(currentSquare, color){
			value = 9;
			this->type = QUEEN;
			if(color == WHITE){
				this->boardChar = 'Q';
			} else {
				this->boardChar = 'q';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getPseudoValidMoves(char board[][8]) override;
};

class King: public Piece {
	public:
		bool a_rook_moved = false, h_rook_moved = false; 
		King(string currentSquare, string color) : Piece(currentSquare, color){
			value = 10000;
			this->type = KING;
			if(color == WHITE){
				this->boardChar = 'K';
			} else {
				this->boardChar = 'k';
			}
		}
		bool isValidMove(string to, char board[][8]) override;
		vector<string> getPseudoValidMoves(char board[][8]) override;
		bool canCastle(string to, char board[][8]);
		vector<Piece*> isInCheck(char board[][8]);
		vector<Piece*> isInCheck(string to, char board[][8]);
};

/*==========================={ Pieces }===========================*/

class Pieces{	
	public:
		vector<Piece*> pieces;
		int material;
		string color;
		static const int starting_material;
		
		virtual ~Pieces(){
		}
		
		Pieces(){	
		}
		
		void printPieces();
		Piece* pieceInSquare(string square, char board[][8]);
		vector<Piece *> isValidMove(string square, char board[][8]);
		int calculateMaterial();
		virtual void loadPieces(char board[][8]) = 0;
};

class WhitePieces : public Pieces{
	public:
		~WhitePieces(){}
		WhitePieces() : Pieces(){
			this->color = Piece::WHITE;
		}

		void loadPieces(char board[][8]) override;
};

class BlackPieces : public Pieces{
	public:
		~BlackPieces(){}
		BlackPieces() : Pieces(){
			this->color = Piece::BLACK;
		}

		void loadPieces(char board[][8]) override;
};

Piece* pieceFromChar(int x, int y, char board[][8]);



