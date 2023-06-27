#pragma once

#include <cstring>
#include <string>
#include <unordered_map>
#include "pieces.h"
// #include "notation.h"

using namespace std;

class Board{
    public:
        string moveFor;

        char board[8][8] = {
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
        };
        
        bool isInCheckmate(King *king);
		bool isInStalemate(King *king);
        bool isProtected(Piece *piece);
        bool isProtected(string square, string color);
        bool isPinned(string to, Piece *piece);
        bool kingTouchesKing(string to, string color);

        bool canMove(Move move, Board *board);
        bool canAttack(Move move, Board *board);
        bool canMove(string color, string square, Board *board);
        bool canAttack(string color, string square, Board *board);
        bool canKingCapturePiece(King *king, Move move, Board *board);
        bool isValidSquare(string square);
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

        


        bool isThreeFoldRepetition();
        bool isDrawDueToInsufficientMaterial();
        bool isFiftyMoveRule();
        
        void resetMovesSinceCapture();
        Pieces* getPieces(string color);
        void setOutcome(string outcome);
        string getOutcome();
        void setKingsCastlingRights(King *king);
        void increaceMovesSinceCapture();
        void setMove1Before(Move move);
        Move getMove1Before();
        void setPGN(string pgn);
        vector<string> getPGNMoves();


        void importFEN(string fen);
        void importPGN(string pgn);
        string exportFEN();
        string exportFEN(char board[][8]);
        string exportPGN();
        
        void printBoard();
        void printBigBoard();
        void scanBoard(vector<Piece*> whitePieces, vector<Piece*> blackPieces);

        Piece *findPiece(string type, string color);
        int findPiece(Piece *piece);
        Piece* findPiece(Coords coords);
        Piece*findPiece(string square);
        
        void pushBoardState(string fen);
        void pushMove(string move);
        int quantityOfPiece(string type, string color);

        static void copyBoard(char src[8][8], char dest[8][8]);
        static void copyMove(Move *src, Move *dest);
        
        


        ~Board(){}
        Board(){};
        Board(string fen){
            importFEN(fen);
            wp->loadPieces(board);
            bp->loadPieces(board);

            setKingsCastlingRights(dynamic_cast<King *>(findPiece(Piece::KING, Piece::WHITE)));
            setKingsCastlingRights(dynamic_cast<King *>(findPiece(Piece::KING, Piece::BLACK)));

            past_board_states.insert({fen, 1});
        }

        Board(char board[8][8]) : Board(exportFEN(board)){}


    private:
        Pieces *wp = new WhitePieces();
        Pieces *bp = new BlackPieces();
        Move move_1_before{"a1", "a1"};
        unordered_map<string, int> past_board_states;
        string outcome = "";
        int moves_since_capture = 0;
        string castling_rights;
        string pgn = "";
        vector<string> pgn_moves;
};
