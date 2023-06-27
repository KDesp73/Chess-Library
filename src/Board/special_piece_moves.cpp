#include "board.h"
#include "board_utils.h"

#include <iostream>
#include <limits>

using namespace BoardUtils;


string Board::promoteTo(){
    char promoteTo = '-';
    do {
        printf("Promote to (q, r, b, n): ");
        cin >> promoteTo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        printf("\n");
    } while (promoteTo != 'q' && promoteTo != 'r' && promoteTo != 'b' && promoteTo != 'n');

    if(promoteTo == 'q') return Piece::QUEEN;
    if(promoteTo == 'r') return Piece::ROOK;
    if(promoteTo == 'b') return Piece::BISHOP;
    if(promoteTo == 'n') return Piece::KNIGHT;

    return "";
}

bool Board::promotePawn(Move move, Pawn *pawn, Board *board){
    if(
        move.promotion != Piece::BISHOP &&
        move.promotion != Piece::KNIGHT &&
        move.promotion != Piece::ROOK &&
        move.promotion != Piece::QUEEN
    ){
        cerr << "Invalid promotion" << endl;
        return false;
    }

    int promotionRank, direction;
    if (pawn->color == "white") {
        promotionRank = 7;
        direction = 1;
    } else{
        promotionRank = 0;
        direction = -1;
    }

    Coords currentCoords = translateSquare(pawn->currentSquare);
    if (currentCoords.x != promotionRank - direction) return false;

    Piece *pieceToCapture = board->findPiece(move.to);
    if(pieceToCapture != NULL){
        Board::removePieceFreely(move.to, board);
    }

    Piece* promoted;
    string color = pawn->color;
    Board::removePieceFreely(pawn->currentSquare, board);

    int promoteTo = -1;
    char piece_char;

    if(move.promotion == Piece::QUEEN) {
        promoteTo = 0;
        piece_char = 'q';    
    }
    else if(move.promotion == Piece::ROOK) {
        promoteTo = 1;
        piece_char = 'r';
    }
    else if(move.promotion == Piece::BISHOP) {
        promoteTo = 2;
        piece_char = 'b';
    }
    else if(move.promotion == Piece::KNIGHT) {
        promoteTo = 3;
        piece_char = 'n';
    }


    switch (promoteTo) {
        case 0:
            promoted = new Queen(move.to, color);
            break;
        case 1:
            promoted = new Rook(move.to, color);
            break;
        case 2:
            promoted = new Bishop(move.to, color);
            break;
        case 3:
            promoted = new Knight(move.to, color);
            break;
        default:
            return false;
    }



    if (pawn->color == "white"){
        board->wp->pieces.push_back(promoted);
        board->board[translateSquare(move.to).x][translateSquare(move.to).y] = toupper(piece_char);
    }
    else {
        board->bp->pieces.push_back(promoted);
        board->board[translateSquare(move.to).x][translateSquare(move.to).y] = piece_char;
    }

    return true;
}

bool Board::castleKing(string square, King *king, Board *board){
    Coords fromCoords = translateSquare(king->currentSquare);
    Coords toCoords = translateSquare(square);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    int direction = toCol - fromCol;
    direction = (direction > 0) ? 1 : -1;

    Rook* wantedRook = BoardUtils::getRookToCastle(direction, king->color, board);

    if (wantedRook == NULL) return false;
    wantedRook->printPiece();

    // Castle
    Board::moveFreely(Move{king->currentSquare, square, "-"}, board);
    string targetRookSquare = translateSquare(Coords{toCoords.x, toCoords.y - direction});
    Board::moveFreely(Move{wantedRook->currentSquare, targetRookSquare, "-"}, board);

    return true;
}

bool Board::enpassantPawn(string square, Pawn *pawn, Board *board){
    char toFile = square.at(0);
    int toRank = square.at(1) - 48;

    int direction = (pawn->color == Piece::WHITE) ? 1 : -1;    

    Board::moveFreely(Move{pawn->currentSquare, square}, board);
    string squareToRemove = string(1, toFile) + to_string(toRank - direction);
    return Board::removePieceFreely(squareToRemove, board);
}