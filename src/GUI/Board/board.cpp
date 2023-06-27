#include "../gui.h"
#include "../../chess_lib.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>

using namespace std;

string getPath(char pieceChar){
    switch (pieceChar){
    case ' ':
        return "";
    case 'p':
        return "bP.png";
    case 'r':
        return "bR.png";
    case 'n':
        return "bN.png";
    case 'b':
        return "bB.png";
    case 'q':
        return "bQ.png";
    case 'k':
        return "bK.png";
    case 'P':
        return "wP.png";
    case 'R':
        return "wR.png";
    case 'N':
        return "wN.png";
    case 'B':
        return "wB.png";
    case 'Q':
        return "wQ.png";
    case 'K':
        return "wK.png";
    default:
        break;
    }
    return "";
}


void GUI::loadPosition(Board *board, SDL_Renderer *renderer){
    int size = GUI::size;
    string pieceTheme = GUI::pieceTheme;

    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 8; j++){
            string path = getPath(board->board[i][j]);
            if(path == "") continue;

            Image image;
            int x, y;
            if(board->getPlayingAs() == "white") {
                x = j;
                y = (7-i);
            } else if(board->getPlayingAs() == "black") {
                x = 7-j;
                y = i;
            } else return;
            string abs_path = SDL_GetBasePath();
            if(abs_path.find("build") != string::npos){
                abs_path.replace(abs_path.find("build"), 5, "assets");
            } else abs_path += "assets/";

            abs_path += pieceTheme + "/";

            image = Rendering::renderImage(abs_path + path, x * size, y * size, renderer);   
            
            for(int k = 0; k < board->getPieces("white")->pieces.size(); k++){
                Coords coords = BoardUtils::translateSquare(board->getPieces("white")->pieces.at(k)->currentSquare);
                if(coords.x == x && coords.y == y){
                    board->getPieces("white")->pieces.at(k)->image = image;
                }
            }
        
            for(int k = 0; k < board->getPieces("black")->pieces.size(); k++){
                Coords coords = BoardUtils::translateSquare(board->getPieces("black")->pieces.at(k)->currentSquare);
                if(coords.x == x && coords.y == y){
                    board->getPieces("black")->pieces.at(k)->image = image;
                }
            }
        }
    }
    IMG_Quit();
}
