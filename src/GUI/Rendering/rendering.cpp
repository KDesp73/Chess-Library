#include "rendering.h"
#include "../gui.h"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

void Rendering::drawBoard(SDL_Color white, SDL_Color black, SDL_Renderer *renderer){
    int rows = 8;
    int columns = 8;
    SDL_Color color;
    int size = GUI::size;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int x = j * GUI::size;
            int y = i * GUI::size;

            // Set the color based on the position
            color = (i + j) % 2 == 0 ? white : black;

            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

            SDL_Rect square = {x, y, GUI::size, GUI::size};
            SDL_RenderFillRect(renderer, &square);
        }
    }
}

Image Rendering::renderImage(string path, int x, int y, SDL_Renderer* renderer) {
    int size = GUI::size;
    SDL_Surface* imageSurface = IMG_Load(path.c_str());
    if (!imageSurface) {
        printf("Failed to load image: %s\n", IMG_GetError());
        return {};
    }

    // Create a new surface with the desired dimensions for the resized image
    SDL_Surface* resizedSurface = SDL_CreateRGBSurface(0, size, size, imageSurface->format->BitsPerPixel,
                                                       imageSurface->format->Rmask, imageSurface->format->Gmask,
                                                       imageSurface->format->Bmask, imageSurface->format->Amask);
    if (!resizedSurface) {
        printf("Failed to create resized surface: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        return {};
    }

    // Resize the original image onto the new surface
    if (SDL_BlitScaled(imageSurface, NULL, resizedSurface, NULL) != 0) {
        printf("Failed to resize image: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_FreeSurface(resizedSurface);
        return {};
    }

    // Create the texture from the resized surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, resizedSurface);
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_FreeSurface(imageSurface);
        SDL_FreeSurface(resizedSurface);
        return {};
    }

    // Get the dimensions of the image
    int imageWidth = resizedSurface->w;
    int imageHeight = resizedSurface->h;

    // Clean up and free resources
    SDL_FreeSurface(imageSurface);
    SDL_FreeSurface(resizedSurface);

    SDL_Rect imageRect;
    imageRect.x = x;                // X coordinate of the top-left corner
    imageRect.y = y;                // Y coordinate of the top-left corner
    imageRect.w = imageWidth;       // Width of the image
    imageRect.h = imageHeight;      // Height
    
    // Render the texture onto the renderer
    SDL_RenderCopy(renderer, texture, nullptr, &imageRect);

    return Image{texture, imageRect};
}

void Rendering::colorSquares(vector<string> squares, string playingAs, SDL_Color red_w, SDL_Color red_b, SDL_Renderer *renderer){
    SDL_Color color;
    for (size_t i = 0; i < squares.size(); i++){
        Coords boardCoords = GUI::getBoardCoordinates(squares.at(i), playingAs);
        color = (boardCoords.x / GUI::size + boardCoords.y / GUI::size) % 2 == 0 ? red_w : red_b;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_Rect square = {boardCoords.x, boardCoords.y, GUI::size, GUI::size};
        SDL_RenderFillRect(renderer, &square);
    }
}