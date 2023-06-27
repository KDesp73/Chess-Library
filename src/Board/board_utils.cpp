#include "board_utils.h"
#include "../Pieces/Pieces.h"
#include "structs.h"

#include <bits/stdc++.h>
#include <iostream>

using namespace std;

Coords BoardUtils::translateSquare(string square) {
    string letters = "abcdefgh";

    int x = square.at(1) - 48 - 1;
    int y = letters.find(square.at(0));

    if ((square.length() < 0 || square.length() > 2) ||
        ((x < 0 || x > 7) && (y < 0 || y > 7))) {
        cout << "Invalid square";
        return {};
    }

    Coords coords{x, y};

    return coords;
}

string BoardUtils::translateSquare(Coords coords) {
    string letters = "abcdefgh";

    string rank, file;

    rank = letters[(coords.y)];
    file = coords.x + 48 + 1;

    return rank + file;
}

char BoardUtils::pieceToMove(Coords coords, char board[][8]) {
    return board[coords.x][coords.y];
}

char BoardUtils::pieceToMove(string square, char board[][8]) {
    Coords coords = translateSquare(square);

    return BoardUtils::pieceToMove(coords, board);
}

bool BoardUtils::makeMove(string from, string to, char board[][8]) {
    Coords fromCoords = translateSquare(from);
    Coords toCoords = translateSquare(to);

    /*if (sizeof(fromCoords) || sizeof(toCoords)) {
        cout << "Empty coords" << endl;
        return false;
    }*/

    char piece = pieceToMove(from, board);

    // cout << "Piece to move: |" << piece << "|" << endl;

    board[fromCoords.x][fromCoords.y] = ' ';
    board[toCoords.x][toCoords.y] = piece;

    return true;
}


void BoardUtils::printCoords(Coords coords) {
    cout << "(" << coords.x << ", " << coords.y << ")" << endl;
}

void BoardUtils::printCoords(string square) {
    Coords coords = translateSquare(square);

    cout << square << " is "
         << "(" << coords.x << ", " << coords.y << ")" << endl;
}

void BoardUtils::emptyBoard(char board[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
}

vector<Piece*> BoardUtils::squareIsAttacked(string square, Pieces* p, char board[][8]) {
    vector<Piece*> list;
    for (int i = 0; i < p->pieces.size(); i++) {
        if ((p->pieces.at(i)->isValidMove(square, board) &&
             p->pieces.at(i)->type != "Pawn") ||
            (p->pieces.at(i)->type == "Pawn" &&
             (dynamic_cast<Pawn*>(p->pieces.at(i)))
                 ->isValidCapture(square, board))) {
            list.push_back(p->pieces.at(i));
        }
    }
    return list;
}

bool BoardUtils::isValidSquare(string square){
    if(square.length() != 2){
        // cout << "Move not 2 characters" << endl;
        return false;
    }
    if(!isalpha(square[0])) {
        // cout << "First character not in alphabet" << endl;
        return false;
    }
    if(!isdigit(square[1])) {
        // cout << "Second character not a digit" << endl;
        return false;
    }
    if(square[1] - 48 < 1 || square[1] - 48 > 8) {
        // cout << "Rank number less than 1 or grater than 8" << endl;
        return false;
    }
    if(square[0] < 'a' || square[0] > 'h') {
        // cout << "File character less than a or grater than h" << endl;
        return false;
    }

    return true;
}

bool BoardUtils::contains(vector<string> moves, string move){
    for (int i = 0; i < moves.size(); i++){
        if(moves.at(i) == move) return true;
    }
    return false;
}

int BoardUtils::kingWantsToCastle(Move move){
    Coords fromCoords = translateSquare(move.from);
    Coords toCoords = translateSquare(move.to);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    if(abs(fromCol - toCol) != 2) return 0;

    return toCol - fromCol;
}

int BoardUtils::calcDirection(King *king, string square){
    Coords fromCoords = translateSquare(king->currentSquare);
    Coords toCoords = translateSquare(square);

    int fromRow = fromCoords.x, fromCol = fromCoords.y;
    int toRow = toCoords.x, toCol = toCoords.y;

    int direction = toCol - fromCol;
    direction = (direction > 0) ? 1 : -1;

    return direction;
}

bool BoardUtils::canKingCapturePiece(King *king, Move move, Board *board){
    Piece *pieceToCapture = NULL;
    // Search white for pieces
    pieceToCapture = board->findPiece(move.to);

    if(pieceToCapture == NULL){
        return true;
    }

    if(pieceToCapture->color == king->color) return false;

    return !(board->isProtected(pieceToCapture));

}

bool BoardUtils::canRookBeBlocked(Rook *rook, King *king, Board *board){
    Coords rookCoords = translateSquare(rook->currentSquare);
    Coords kingCoords = translateSquare(king->currentSquare);

    int rookRow = rookCoords.x, rookCol = rookCoords.y;
    int kingRow = kingCoords.x, kingCol = kingCoords.y;

    string letters = "abcdefgh";

    if (rookRow == kingRow) {
        for (int i = 1; i <= abs(rookCol - kingCol); i++) {
            string squareToCheck = letters[i] + to_string(rookRow + 1);
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    } else if (rookCol == kingCol) {
        for (int i = 1; i <= abs(rookRow - kingRow); i++) {
            string squareToCheck = letters[rookCol - 1] + to_string(i + 1);
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    }
    return false;
}

bool BoardUtils::canBishopBeBlocked(Bishop *bishop, King *king, Board *board){
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
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    } else if(rowDiff < 0 && colDiff > 0){
        for (int i = 1; i <= abs(rowDiff); i++){
            string squareToCheck = letters[bishopCoords.y - i] + to_string(bishopCoords.x + 1 + i);
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    } else if(rowDiff > 0 && colDiff < 0){
        for (int i = 1; i <= abs(rowDiff); i++){
            string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 - i);
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    } else if(rowDiff < 0 && colDiff < 0){
        for (int i = 1; i <= abs(rowDiff); i++){
            string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 + i);
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    }

    return false;
}

bool BoardUtils::canQueenBeBlocked(Queen *queen, King *king, Board *board){
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
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    } else if (queenCol == kingCol) {
        int direction = (rowDiff < 0) ? 1 : -1;
        for (int i = 1; i < abs(queenRow - kingRow); i++) {
            string squareToCheck = letters[queenCol - 1] + to_string(queenRow - 1 + i*direction);
            if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
        }
    } else {
        // Bishop check
        if(abs(colDiff) != abs(rowDiff)) return false;
        if(rowDiff > 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 - i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
            }
        } else if(rowDiff < 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 + i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
            }
        } else if(rowDiff > 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 - i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
            }
        } else if(rowDiff < 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 + i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                return true;
            }
        }
    }

    return false;
}

bool BoardUtils::canPieceBeBlocked(Piece *piece, King *king, Board *board){
    Pawn *pawn = dynamic_cast<Pawn *>(piece);
    Rook *rook = dynamic_cast<Rook *>(piece);
    Knight *knight = dynamic_cast<Knight *>(piece);
    Bishop *bishop = dynamic_cast<Bishop *>(piece);
    Queen *queen = dynamic_cast<Queen *>(piece);

    if (knight != NULL) return false;
    if (pawn != NULL) return false;

    if (rook != NULL) {
        Coords rookCoords = translateSquare(rook->currentSquare);
        Coords kingCoords = translateSquare(king->currentSquare);

        int rookRow = rookCoords.x, rookCol = rookCoords.y;
        int kingRow = kingCoords.x, kingCol = kingCoords.y;

        string letters = "abcdefgh";

        if (rookRow == kingRow) {
            for (int i = 1; i <= abs(rookCol - kingCol); i++) {
                string squareToCheck = letters[i] + to_string(rookRow + 1);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
            }
        } else if (rookCol == kingCol) {
            for (int i = 1; i <= abs(rookRow - kingRow); i++) {
                string squareToCheck = letters[rookCol - 1] + to_string(i + 1);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
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
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
            }
        } else if(rowDiff < 0 && colDiff > 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y - i] + to_string(bishopCoords.x + 1 + i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
            }
        } else if(rowDiff > 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 - i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
            }
        } else if(rowDiff < 0 && colDiff < 0){
            for (int i = 1; i <= abs(rowDiff); i++){
                string squareToCheck = letters[bishopCoords.y + i] + to_string(bishopCoords.x + 1 + i);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
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
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
            }
        } else if (queenCol == kingCol) {
            int direction = (rowDiff < 0) ? 1 : -1;
            for (int i = 1; i < abs(queenRow - kingRow); i++) {
                string squareToCheck = letters[queenCol - 1] + to_string(queenRow - 1 + i*direction);
                if (BoardUtils::canMove(king->color, squareToCheck, board))
                    return true;
            }
        } else {
            // Bishop check
            if(abs(colDiff) != abs(rowDiff)) return false;
            if(rowDiff > 0 && colDiff > 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 - i);
                    if (BoardUtils::canMove(king->color, squareToCheck, board))
                        return true;
                }
            } else if(rowDiff < 0 && colDiff > 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y - i] + to_string(queenCoords.x + 1 + i);
                    if (BoardUtils::canMove(king->color, squareToCheck, board))
                        return true;
                }
            } else if(rowDiff > 0 && colDiff < 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 - i);
                    if (BoardUtils::canMove(king->color, squareToCheck, board))
                        return true;
                }
            } else if(rowDiff < 0 && colDiff < 0){
                for (int i = 1; i <= abs(rowDiff); i++){
                    string squareToCheck = letters[queenCoords.y + i] + to_string(queenCoords.x + 1 + i);
                    if (BoardUtils::canMove(king->color, squareToCheck, board))
                        return true;
                }
            }
        }
    }
    return false;
}

Rook* BoardUtils::getRookToCastle(int direction, string color, Board *board) {
    Piece* wantedRook;
    if (direction > 0 && color == "white") {
        wantedRook = board->findPiece(Coords{0, 7});
    } else if (direction < 0 && color == "white") {
        wantedRook = board->findPiece(Coords{0, 0});
    } else if (direction > 0 && color == "black") {
        wantedRook = board->findPiece(Coords{7, 7});
    } else if (direction < 0 && color == "black") {
        wantedRook = board->findPiece(Coords{7, 0});
    } else {
        cout << "Something went wrong" << endl;
    }

    return dynamic_cast<Rook*>(wantedRook);
}

string BoardUtils::offsetSquare(string square, int offset_v, int offset_h){
    Coords coords = translateSquare(square);

    coords.x += offset_v;
    coords.y += offset_h;

    string ret = translateSquare(coords);
    return ret;
}

bool BoardUtils::canAttack(Move move, Board *board){
    if(board->findPiece(move.from)->type != Piece::PAWN){
        return BoardUtils::canMove(move, board);
    } else {
        Pawn *pawn = dynamic_cast<Pawn *>(board->findPiece(move.from));

        if(pawn == NULL) return false;

        if(pawn->attacksSquare(move.to, board->board)) {
            if(!board->isPinned(move.to, pawn)){
                return true;
            }
        }
    }
    return false;
}

bool BoardUtils::canAttack(string color, string square, Board *board){
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
        if (BoardUtils::canAttack(move, board)) return true;
    }
    return false;
}