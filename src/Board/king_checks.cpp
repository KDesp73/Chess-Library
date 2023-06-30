#include "board.h"
#include "board_utils.h"
#include "movement.h"

using namespace BoardUtils;

bool Movement::isInCheckmate(King *king, Board *board) {
    vector<Piece *> piecesThatCheckTheKing = king->isInCheck(board->board);

    if (piecesThatCheckTheKing.empty()) return false;

    vector<string> kingsValidMoves = Movement::getValidMoves(king, board);
    
    // Filter invalid moves once more checking protected pieces
    for (int i = 0; i < kingsValidMoves.size(); i++){
        if(!Movement::canMove(Move{king->currentSquare, kingsValidMoves.at(i)}, board)) {
            kingsValidMoves.erase(kingsValidMoves.begin() + i);  // erase from vector
            i--;
        }
    }

    if (!kingsValidMoves.empty()) return false;
    if (piecesThatCheckTheKing.size() > 1) return true;
    // Check if piece that checks the king can be captured
    if(Movement::canMove(king->color, piecesThatCheckTheKing.at(0)->currentSquare, board)) return false;

    // Check if check can be blocked
    Pawn *pawn = dynamic_cast<Pawn *>(piecesThatCheckTheKing.at(0));
    Rook *rook = dynamic_cast<Rook *>(piecesThatCheckTheKing.at(0));
    Knight *knight = dynamic_cast<Knight *>(piecesThatCheckTheKing.at(0));
    Bishop *bishop = dynamic_cast<Bishop *>(piecesThatCheckTheKing.at(0));
    Queen *queen = dynamic_cast<Queen *>(piecesThatCheckTheKing.at(0));

    if (knight != NULL) return true;
    if (pawn != NULL) return true;

    if (rook != NULL) {
        Coords rookCoords = translateSquare(rook->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int rookRow = rookCoords.x, rookCol = rookCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        string letters = "abcdefgh";

        if (rookRow == kingRow) {
            int direction = (rookCol < kingCol) ? 1 : -1;
            for (int i = 1; i <= abs(rookCol - kingCol); i++) {
                string squareToCheck = letters[rookCol + i * direction] + to_string(rookRow + 1);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        } else if (rookCol == kingCol) {
            int direction = (rookRow < rookCol) ? 1 : -1;
            for (int i = 1; i <= abs(rookRow - kingRow); i++) {
                string squareToCheck = letters[rookCol] + to_string(rookRow + i * direction + 1);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        }
    }

    if (bishop != NULL){
        Coords bishopCoords = translateSquare(bishop->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int bishopRow = bishopCoords.x, bishopCol = bishopCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        int rowDiff = bishopRow - kingRow;
        int colDiff = bishopCol - kingCol;

        string letters = "abcdefgh";

        if(rowDiff > 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y - i] + to_string(bishopCoords.x + 1 - i);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        } else if(rowDiff < 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y - i] + to_string(bishopCoords.x + 1 + i);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        } else if(rowDiff > 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 - i);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        } else if(rowDiff < 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 + i);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        }
    }

    if(queen != NULL){ 
        Coords queenCoords = translateSquare(queen->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int queenRow = queenCoords.x, queenCol = queenCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        int rowDiff = queenRow - kingRow;
        int colDiff = queenCol - kingCol;

        string letters = "abcdefgh";

        // Rook check
        if (queenRow == kingRow) {
            int direction = (colDiff < 0) ? 1 : -1;
            for (int i = 1; i < abs(queenCol - kingCol); i++) {
                string squareToCheck = letters[queenCol + i*direction] + to_string(queenRow + 1);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        } else if (queenCol == kingCol) {
            int direction = (rowDiff < 0) ? 1 : -1;
            for (int i = 1; i < abs(queenRow - kingRow); i++) {
                string squareToCheck = letters[queenCol] + to_string(queenRow - 1 + i*direction);
                if (Movement::canMove(king->color, squareToCheck, board))
                    return false;
            }
        } else {
            // Bishop check
            if(abs(colDiff) != abs(rowDiff)) return false;
            if(rowDiff > 0 && colDiff > 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 - i);
                    if (Movement::canMove(king->color, squareToCheck, board))
                        return false;
                }
            } else if(rowDiff < 0 && colDiff > 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 + i);
                    if (Movement::canMove(king->color, squareToCheck, board))
                        return false;
                }
            } else if(rowDiff > 0 && colDiff < 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 - i);
                    if (Movement::canMove(king->color, squareToCheck, board))
                        return false;
                }
            } else if(rowDiff < 0 && colDiff < 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 + i);
                    if (Movement::canMove(king->color, squareToCheck, board))
                        return false;
                }
            }
        }
    }

    return true;
}

bool Movement::isInStalemate(King *king, Board *board) {
    if(king->color != board->moveFor) return false;
    
    vector<Piece *> piecesThatCheckTheKing = king->isInCheck(board->board);

    if(!piecesThatCheckTheKing.empty()) return false;

    if(!Movement::getValidMoves(king, board).empty()) return false;

    Pieces *pieces = board->getPieces(king->color);

    for (int i = 0; i < pieces->pieces.size(); i++){
        if(pieces->pieces.at(i)->type == Piece::KING) continue;

        if(!Movement::getValidMoves(pieces->pieces.at(i), board).empty()) return false;
    }

    return true;
};

bool Movement::kingTouchesKing(string to, string color, Board *board){
    King *opponent_king = dynamic_cast<King *>(board->findPiece(Piece::KING, (color == Piece::WHITE) ? Piece::BLACK : Piece::WHITE));

    if(opponent_king == NULL) {
        //cerr << "Opponent king not found" << endl;
        return false;
    }

    Coords kingCoords = translateSquare(to);
    Coords opponentCoords = translateSquare(opponent_king->currentSquare);

    int kingRow = kingCoords.x, kingCol = kingCoords.y;
    int oppnentRow = opponentCoords.x, opponentCol = opponentCoords.y;

    int rowDiff = oppnentRow - kingRow;
    int colDiff = opponentCol - kingCol;

    return (abs(rowDiff) <= 1 && abs(colDiff) <= 1);
}

