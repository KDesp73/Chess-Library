#pragma once

#include "board.h"
#include "pieces.h"

namespace Movement{
    bool isInCheckmate(King *king, Board *board);
    bool isInStalemate(King *king, Board *board);
    bool isProtected(Piece *piece, Board *board);
    bool isProtected(string square, string color, Board *board);
    bool isPinned(string to, Piece *piece, Board *board);
    bool kingTouchesKing(string to, string color, Board *board);

    bool canMove(Move move, Board *board);
    bool canAttack(Move move, Board *board);
    bool canMove(string color, string square, Board *board);
    bool canAttack(string color, string square, Board *board);
    bool canKingCapturePiece(King *king, Move move, Board *board);
    int kingWantsToCastle(Move move);

    vector<string> getValidMoves(Piece *piece, Board *board);
    bool movePiece(Move move, Board *board);
    void moveFreely(Move move, Board *board);
    bool removePiece(string square, Board *board);
    bool removePieceFreely(string square, Board *board);


    bool promotePawn(Move move, Pawn *pawn, Board *board);
    string promoteTo();
    bool enpassantPawn(string square, Pawn *pawn, Board *board);
    bool castleKing(string square, King *king, Board *board);
};