#include "board.h"
#include "movement.h"

static string starting_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

int main(){
    system("clear");

    Board board{"r1q1kbnr/p1Bb1ppp/2Q5/8/8/2pP1N2/P4PPP/2K1RB1R b"};

    board.printBigBoard();
    
    
    
    return 0;
}
