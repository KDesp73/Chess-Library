#include "board.h"
#include "movement.h"


static string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main(){
    system("clear");

    Board board{starting_fen};

    board.printBigBoard();
    Movement::movePiece(Move{"e2", "e4"}, &board);
    board.swapMoveFor();
    board.printBigBoard();

    for(string move : Movement::getValidMoves("b1", &board)){
        cout << move << endl;
    }

    return 0;
}