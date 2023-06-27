#include <bits/stdc++.h>

#include <iostream>

#include "pieces.h"
#include "notation.h"
#include "board_utils.h"
#include "structs.h"
#include "movement.h"

using namespace BoardUtils;

bool Movement::movePiece(Move move, Board *board) {
    string current_fen = board->exportFEN();
    int moveIndex, captureIndex;
    Piece *pieceToMove = nullptr;
    Piece *pieceToCapture = nullptr;
    Pieces *whitePieces = board->getPieces(Piece::WHITE);
    Pieces *blackPieces = board->getPieces(Piece::BLACK);

    pieceToMove = board->findPiece(move.from);
    pieceToCapture = board->findPiece(move.to);

    if (pieceToMove == NULL) return false;

    Pawn *pawn = dynamic_cast<Pawn *>(pieceToMove);
    Rook *rook = dynamic_cast<Rook *>(pieceToMove);
    Knight *knight = dynamic_cast<Knight *>(pieceToMove);
    Bishop *bishop = dynamic_cast<Bishop *>(pieceToMove);
    Queen *queen = dynamic_cast<Queen *>(pieceToMove);
    King *king = dynamic_cast<King *>(pieceToMove);

    if (pieceToMove->color != board->moveFor) return false;

    // Pawn Promotion
    if (pawn != NULL && pawn->canPromote(move.to, board->board)) {
        if(move.promotion == "-" || move.promotion == ""){
            move.promotion = Movement::promoteTo();
        }

        if (Movement::canMove(move, board) && move.promotion != "-" && move.promotion != "") {
            board->setMove1Before(move);
            board->pushBoardState(board->exportFEN());

            string algebraic_notation =
                Notation::moveToPGNMove(move, new Board(current_fen));
            board->getPGNMoves().push_back(algebraic_notation);

            return Movement::promotePawn(move, pawn, board);
        }
        return false;
    }

    // En passant
    if (pawn != NULL && pawn->canEnpassant(move.to, board->getMove1Before())) {
        board->setMove1Before(move);

        board->pushBoardState(board->exportFEN());

        string algebraic_notation =
            Notation::moveToPGNMove(move, new Board(current_fen));
        board->getPGNMoves().push_back(algebraic_notation);
        return Movement::enpassantPawn(move.to, pawn, board);
    }

    // Castle
    if (king != NULL && kingWantsToCastle(move) != 0 &&
        king->canCastle(move.to, board->board)) {
        board->setMove1Before(move);

        board->pushBoardState(board->exportFEN());

        string algebraic_notation =
            Notation::moveToPGNMove(move, new Board(current_fen));
        board->getPGNMoves().push_back(algebraic_notation);
        return Movement::castleKing(move.to, king, board);
    }

    if (!canMove(move, board) && !canMove(move, board) &&
        !canMove(move, board) && !canMove(move, board) &&
        !canMove(move, board) && !canMove(move, board))
        return false;

    // Capture the piece
    if (!Movement::removePiece(move.to, board))
        board->increaceMovesSinceCapture();
    else
        board->resetMovesSinceCapture();

    // Make the move
    bool moveMade = makeMove(pieceToMove->currentSquare, move.to, board->board);
    if (moveMade) {
        board->setMove1Before(move);

        board->pushBoardState(board->exportFEN());

        string algebraic_notation =
            Notation::moveToPGNMove(move, new Board(current_fen));
        board->pushMove(algebraic_notation);

        if (translateSquare(pieceToMove->currentSquare).y == 0 &&
            pieceToMove->type == "Rook")
            dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))
                ->a_rook_moved = true;
        if (translateSquare(pieceToMove->currentSquare).y == 7 &&
            pieceToMove->type == "Rook")
            dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))
                ->h_rook_moved = true;

        pieceToMove->currentSquare = move.to;
        pieceToMove->hasMoved = true;
    }
    return moveMade;
}

void Movement::moveFreely(Move move, Board *board) {
    string current_fen = board->exportFEN();
    int moveIndex, captureIndex;
    Piece *pieceToMove = NULL;
    Piece *pieceToCapture = NULL;
    Pieces *whitePieces = board->getPieces(Piece::WHITE);
    Pieces *blackPieces = board->getPieces(Piece::BLACK);

    pieceToMove = board->findPiece(move.from);
    pieceToCapture = board->findPiece(move.to);

    Pawn *pawn = dynamic_cast<Pawn *>(pieceToMove);
    Rook *rook = dynamic_cast<Rook *>(pieceToMove);
    Knight *knight = dynamic_cast<Knight *>(pieceToMove);
    Bishop *bishop = dynamic_cast<Bishop *>(pieceToMove);
    Queen *queen = dynamic_cast<Queen *>(pieceToMove);
    King *king = dynamic_cast<King *>(pieceToMove);

    // Special piece functionality
    if (pawn != NULL && pawn->canPromote(move.to, board->board)) {
        Movement::promotePawn(move, pawn, board);
    }

    // Capture the piece
    if (!Movement::removePiece(move.to, board))
        board->increaceMovesSinceCapture();
    else
        board->resetMovesSinceCapture();

    // Make the move
    bool moveMade = makeMove(move.from, move.to, board->board);
    if (moveMade) {
        board->setMove1Before(move);

        board->pushBoardState(board->exportFEN());

        if (translateSquare(pieceToMove->currentSquare).y == 0 &&
            pieceToMove->type == "Rook")
            dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))
                ->a_rook_moved = true;
        if (translateSquare(pieceToMove->currentSquare).y == 7 &&
            pieceToMove->type == "Rook")
            dynamic_cast<King *>(board->findPiece("King", pieceToMove->color))
                ->h_rook_moved = true;

        pieceToMove->currentSquare = move.to;
        pieceToMove->hasMoved = true;
    }
}

bool Movement::canMove(Move move, Board *board) {
    Piece *piece = board->findPiece(move.from);
    if (piece == NULL || piece == nullptr) return false;

    int direction = (piece->color == Piece::WHITE) ? 1 : -1;
    King *king = dynamic_cast<King *>(piece);

    if(king != NULL && Movement::kingTouchesKing(move.to, piece->color, board)) return false;

    if (king != NULL && !Movement::canKingCapturePiece(king, move, board))
        return false;


    if (king == NULL && Movement::isPinned(move.to, piece, board)) return false;

    // If the King in check, see if the move resolves the check
    if (piece->type != Piece::KING) {
        King *kingInCheck =
            dynamic_cast<King *>(board->findPiece(Piece::KING, piece->color));
        bool isKingInCheck = !kingInCheck->isInCheck(board->board).empty();
        if (isKingInCheck) {
            Board *temp_board = new Board(board->exportFEN());

            if (piece->type == Piece::PAWN) {
                if (dynamic_cast<Pawn *>(piece)->isValidCapture(
                        move.to, temp_board->board)) {
                    Movement::moveFreely(move, temp_board);
                    King *kingInCheckAfterMove = dynamic_cast<King *>(
                        temp_board->findPiece(Piece::KING, piece->color));
                    bool isKingInCheckAfter =
                        !kingInCheckAfterMove->isInCheck(temp_board->board)
                             .empty();
                    return !isKingInCheckAfter;
                }
                // string enpassant_square = BoardUtils::offsetSquare(move.to, direction, 0);
                if (dynamic_cast<Pawn *>(piece)->canEnpassant(
                        move.to, board->getMove1Before())) {
                    /*
                     */

                    Movement::enpassantPawn(
                        move.to,
                        dynamic_cast<Pawn *>(
                            temp_board->findPiece(piece->currentSquare)),
                        temp_board);

                    King *kingInCheckAfterMove = dynamic_cast<King *>(
                        temp_board->findPiece(Piece::KING, piece->color));
                    bool isKingInCheckAfter =
                        !kingInCheckAfterMove->isInCheck(temp_board->board).empty();
                    return !isKingInCheckAfter;
                }
            }

            if (piece->isValidMove(move.to, temp_board->board))
                Movement::moveFreely(move, temp_board);

            King *kingInCheckAfterMove = dynamic_cast<King *>(
                temp_board->findPiece(Piece::KING, piece->color));
            bool isKingInCheckAfter =
                !kingInCheckAfterMove->isInCheck(temp_board->board).empty();
            return !isKingInCheckAfter;
        }
    }

    // Allow special pawn moves
    if (piece->type == Piece::PAWN) {
        if (dynamic_cast<Pawn *>(piece)->isValidCapture(move.to, board->board))
            return true;
        if (dynamic_cast<Pawn *>(piece)->canEnpassant(move.to,
                                                      board->getMove1Before()))
            return true;
        if (dynamic_cast<Pawn *>(piece)->canPromote(move.to, board->board))
            return true;
    }

    // Pseudo-validation
    return piece->isValidMove(move.to, board->board);
}

bool Movement::canMove(string color, string square, Board *board) {
    Pieces *pieces = board->getPieces(color);
    for (int i = 0; i < pieces->pieces.size(); i++) {
        Piece *piece = pieces->pieces.at(i);
        Move move = {piece->currentSquare, square};

        if(piece->type == Piece::PAWN){
            Pawn *pawn = dynamic_cast<Pawn *>(piece);
            string enpassant_square = BoardUtils::offsetSquare(square, (color == "white") ? 1 : -1, 0);
            if(pawn->canEnpassant(enpassant_square, board->getMove1Before())){
                return true;
            }
        }
        if (Movement::canMove(move, board)) return true;
    }
    return false;
}

