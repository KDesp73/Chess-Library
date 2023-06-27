#include "board.h"


static string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main(){
    system("clear");

    Board board{starting_fen};

    board.printBigBoard();

    Board::movePiece(Move{"e2", "e4"}, &board);

    board.printBigBoard();
    return 0;
}