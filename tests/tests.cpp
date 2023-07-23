# include "tests.h"

#include "../src/chess_lib.h"
#include "../src/Board/board_utils.h"
#include "../Ansi-Text-Manipulation-Library/AnsiTextLibrary/src/ansi_lib.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace BoardUtils;
using namespace AnsiTextLib;

bool Test::testCheckMate(vector<string> mate_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Mate...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < mate_fens.size(); i++){
		Board b{mate_fens.at(i)};
		//b.printBigBoard();

		Piece *w_p = b.findPiece("King", "white");
		King *w_king = dynamic_cast<King *>(w_p);
		
		if(b.isInCheckmate(w_king)) {
			passed_count++;
			cout << Text::green + "Passed\n" + Text::normal;
			
		}else{
			passed = false;
			failed_count++;
			cout << Text::red + "Failed" + Text::normal +" at: " + mate_fens.at(i) + "\n";
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testCheckMate(string mate_fen){
	return Test::testCheckMate(vector<string>{mate_fen});
}


bool Test::testCheck(vector<string> check_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Checks...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < check_fens.size(); i++){
		Board b{check_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);
		//printValidMoves(king, temp_fen);

		(!king->isInCheck(b.board).empty()) ? cout << Text::green + "Passed\n" + Text::normal : cout << Text::red + "Failed" + Text::normal +" at: " + check_fens.at(i) + "\n";
	
		if(king->isInCheck(b.board).empty()) {
			passed = false;
			failed_count++;
		}else{
			passed_count++;
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testCheck(string check_fen){
	return Test::testCheck(vector<string>{check_fen});
}


bool Test::testNotCheck(vector<string> should_not_be_check_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Not in Check...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < should_not_be_check_fens.size(); i++){
		Board b{should_not_be_check_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);
		//printValidMoves(king, temp_fen);

		(king->isInCheck(b.board).empty()) ? cout << Text::green + "Passed\n" + Text::normal : cout << Text::red + "Failed" + Text::normal +" at: " + should_not_be_check_fens.at(i) + "\n";
	
		if(!king->isInCheck(b.board).empty()) {
			passed = false;
			failed_count++;
		}else{
			passed_count++;
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testNotCheck(string should_not_be_check_fen){
	return Test::testNotCheck(vector<string>{should_not_be_check_fen});
}

bool Test::testStaleMate(vector<string> stalemate_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Stalemate...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < stalemate_fens.size(); i++){
		Board b{stalemate_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);

		if(b.isInStalemate(king)) {
			passed_count++;
			cout << Text::green + "Passed\n" + Text::normal;
			
		}else{
			passed = false;
			failed_count++;
			cout << Text::red + "Failed" + Text::normal +" at: " + stalemate_fens.at(i) + "\n";
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}

bool Test::testStaleMate(string stalemate_fen){
	return Test::testStaleMate(vector<string>{stalemate_fen});
}

bool Test::testDrawDueToInsufficientMaterial(vector<string> ddtim_fens){
	int passed_count = 0, failed_count = 0;
	Text::clearScreen();
	cout << Text::b_cyan + "Testing Draw due to insufficient material...\n" + Text::normal << endl;
	bool passed = true;
	for (int i = 0; i < ddtim_fens.size(); i++){
		Board b{ddtim_fens.at(i)};
		//b.printBigBoard();

		Piece *p = b.findPiece("King", "white");
		King *king = dynamic_cast<King *>(p);

		if(b.isDrawDueToInsufficientMaterial()) {
			passed_count++;
			cout << Text::green + "Passed\n" + Text::normal;
			
		}else{
			passed = false;
			failed_count++;
			cout << Text::red + "Failed" + Text::normal +" at: " + ddtim_fens.at(i) + "\n";
		}
	}

	cout << endl << endl << Text::green + "Passed: " + to_string(passed_count) + Text::normal << endl;
	cout << Text::red + "Failed: " + to_string(failed_count) + Text::normal << endl;

	return passed;
}