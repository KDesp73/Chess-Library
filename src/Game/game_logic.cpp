#include <iostream>

#include "game_logic.h"
#include "game_utils.h"
#include "../Pieces/Pieces.h"
#include "../Board/board.h"
#include "../Board/board_utils.h"
#include "../Notation/notation.h"





void Game::start(Board *board, string interface){
	if(interface == Board::CLI){
		board->printBigBoard();
		GameUtils::gameLoop(board);
	} else if(interface == Board::GUI){
		GUI::init(board->getSize(), board->getTheme(), board);
	}
}


void GameUtils::gameLoop(Board *board){

	string playing = board->moveFor;
	
	while(!GameUtils::isMate(board) && !GameUtils::isDraw(board)){
		if(playing == "white"){
			cout << "White's turn" << endl;

			Move moveMade = GameUtils::turn(board->getPieces(Piece::WHITE), board);
			if(moveMade.from != "" && moveMade.to != "")
				playing = "black";
		} else {
			cout << "Black's turn" << endl;
			Move moveMade = GameUtils::turn(board->getPieces(Piece::BLACK), board);
			if(moveMade.from != "" && moveMade.to != "")
				playing = "white";
		}
		board->moveFor = playing;
	}
}

Move GameUtils::turn(Pieces *p, Board *board){
	Move move = GameUtils::prompt(p, board, board->getPromptType());
	if(move.from == "" || move.to == "" || sizeof(move) == 0) {
		return {};
	}
	bool moveMade = Board::movePiece(move, board);
	if(moveMade)
		board->printBigBoard();

	return move;
}

Move GameUtils::prompt(Pieces* p, Board *board, string type){
	string from, to;
	string end_keycode = "#end";
	
	if(type == Board::SEPERATE){
		cout << "From: ";
		cin >> from;
		
		if(from == end_keycode){
			cout << "\nFEN: " << board->exportFEN() << endl;
			cout << "PGN: " << Notation::exportPGN(board) << endl;
			exit(0);
		}
		
		cout << "To: ";
		cin >> to;

		if(to == end_keycode){
			cout << "\nFEN: " << board->exportFEN() << endl;
			cout << "PGN: " << Notation::exportPGN(board) << endl;
			exit(0);
		}
	} else if(type == Board::ONELINE){
		string move;
		cout << "Move: ";
		cin >> move;

		if(move == end_keycode){
			cout << "\nFEN: " << board->exportFEN() << endl;
			cout << "PGN: " << Notation::exportPGN(board) << endl;
			exit(0);
		}

		if(move.size() != 4) return {};

		from = move.substr(0, 2);
		to = move.substr(2, 2);
	} else cerr << "Something went wrong" << endl;

	cout << endl;

	if(!BoardUtils::isValidSquare(from) || !BoardUtils::isValidSquare(to)) {
		cout << "Invalid squares" << endl;
		return {};
	}
	
	return Move{from, to};
}

bool GameUtils::isMate(Board *board){
	if(board->isInCheckmate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::WHITE)))){
		cout << endl << "White is in checkmate" << endl << "Black Wins!" << endl;
		board->setOutcome("0-1");
		return true;
	} else if(board->isInCheckmate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::BLACK)))){
		cout << endl << "Black is in checkmate" << endl << "White Wins!" << endl;
		board->setOutcome("1-0");
		return true;
	}

	return false;
}

bool GameUtils::isDraw(Board *board){
	bool draw = false;

	if(board->isInStalemate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::WHITE)))){
		cout << endl << "White is in stalemate";
		draw =  true;
	} else if(board->isInStalemate(dynamic_cast<King *>(board->findPiece(Piece::KING, Piece::BLACK)))){
		cout << endl << "Black is in stalemate";
		draw =  true;
	} else if(board->isThreeFoldRepetition()){
		cout << endl << "Three fold repetition occured";
		draw =  true;
	} else if(board->isDrawDueToInsufficientMaterial()){
		cout << endl << "Draw due to insufficient material";
		draw =  true;
	} else if(board->isFiftyMoveRule()){
		cout << endl << "50 moves passed and no capture occured";
		draw =  true;
	}

	if(draw){
		cout << endl << "It's a draw" << endl;
		board->setOutcome("1/2-1/2");
	}

	return draw;
}
