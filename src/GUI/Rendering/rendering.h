#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>

using namespace std;

struct Image {
    SDL_Texture* texture;
    SDL_Rect rect;
};

namespace Rendering{
    void drawBoard(SDL_Color white, SDL_Color black, SDL_Renderer *renderer);
    Image renderImage(string path, int x, int y, SDL_Renderer *renderer);
    void colorSquares(vector<string> squares, string playingAs, SDL_Color red_w, SDL_Color red_b, SDL_Renderer *renderer);
};