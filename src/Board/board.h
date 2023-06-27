#pragma once

#include <cstring>
#include <string>
#include <unordered_map>
#include "../Pieces/Pieces.h"
// #include "../Notation/notation.h"

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
        bool isThreeFoldRepetition();
        bool isDrawDueToInsufficientMaterial();
        bool isFiftyMoveRule();
        bool isProtected(Piece *piece);
        bool isProtected(string square, string color);
        bool isPinned(string to, Piece *piece);
        bool kingTouchesKing(string to, string color);

        void resetMovesSinceCapture();
        Pieces* getPieces(string color);
        void setOutcome(string outcome);
        string getOutcome();
        void setKingsCastlingRights(King *king);
        void increaceMovesSinceCapture();
        void setMove1Before(Move move);
        Move getMove1Before();
        string getTheme();
        int getSize();
        void setTheme(string theme);
        void setSize(int size);
        string getPromptType();
        string getPlayingAs();
        void setPGN(string pgn);
        vector<string> getPGNMoves();


        void importFEN(string fen);
        void importPGN(string pgn);
        string exportFEN();
        string exportFEN(char board[][8]);
        
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
        static vector<string> getValidMoves(Piece *piece, Board *board);
        static bool movePiece(Move move, Board *board);
        static void moveFreely(Move move, Board *board);
        static bool removePiece(string square, Board *board);
        static bool removePieceFreely(string square, Board *board);

        static bool promotePawn(Move move, Pawn *pawn, Board *board);
        static string promoteTo();
        static bool enpassantPawn(string square, Pawn *pawn, Board *board);
        static bool castleKing(string square, King *king, Board *board);
        
        


        ~Board(){}
        Board(){};
        Board(string fen, string playingAs = Piece::WHITE, bool showMaterial = true, bool showMoves = true, string prompt_type = Board::SEPERATE, int window_size = 60, string theme = Board::WIKI){
            this->playingAs = playingAs;
            this->showMaterial = showMaterial;
            this->showMoves = showMoves;
            this->prompt_type = prompt_type;
            this->window_size = window_size;
            this->theme = theme;

            importFEN(fen);
            wp->loadPieces(board);
            bp->loadPieces(board);

            setKingsCastlingRights(dynamic_cast<King *>(findPiece(Piece::KING, Piece::WHITE)));
            setKingsCastlingRights(dynamic_cast<King *>(findPiece(Piece::KING, Piece::BLACK)));

            past_board_states.insert({fen, 1});
        }

        Board(char board[8][8], string playingAs = Piece::WHITE, bool showMaterial = true, bool showMoves = true, string prompt_type = Board::SEPERATE, int window_size = 60, string theme = Board::WIKI)
        : Board(exportFEN(board), playingAs, showMaterial, showMoves, prompt_type, window_size, theme){}


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
        string playingAs;
        bool showMaterial;
        bool showMoves;
        string prompt_type;
        int window_size;
        string theme;

    public:
        static const string ONELINE;
        static const string SEPERATE;
        static const string GUI;
        static const string CLI;
        static const string WIKI;
        static const string MERIDA;
        static const string STAUNTY;
};
