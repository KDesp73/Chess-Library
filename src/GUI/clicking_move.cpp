#include <SDL.h>
#include <iostream>
#include <string>

// Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int BOARD_SIZE = 8;
const int SQUARE_SIZE = SCREEN_WIDTH / BOARD_SIZE;

// Struct for move information
struct Move {
    std::string from;
    std::string to;
};

// Helper function to convert screen coordinates to board coordinates
std::string getBoardCoordinates(int x, int y) {
    int file = x / SQUARE_SIZE;
    int rank = y / SQUARE_SIZE;
    std::string fileStr = std::string(1, 'A' + file);
    std::string rankStr = std::to_string(BOARD_SIZE - rank);
    return fileStr + rankStr;
}

int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the window
    SDL_Window* window = SDL_CreateWindow("Chessboard", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Event loop
    bool quit = false;
    SDL_Event event;
    bool isPieceSelected = false;
    std::string fromSquare;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if a valid square is clicked
                if (x < BOARD_SIZE * SQUARE_SIZE && y < BOARD_SIZE * SQUARE_SIZE) {
                    std::string clickedSquare = getBoardCoordinates(x, y);

                    if (!isPieceSelected) {
                        // Select a piece
                        fromSquare = clickedSquare;
                        isPieceSelected = true;
                    } else {
                        // Release the piece and make the move
                        Move move = {fromSquare, clickedSquare};
                        std::cout << "Move: " << move.from << " to " << move.to << std::endl;
                        isPieceSelected = false;
                    }
                }
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the chessboard
        for (int rank = 0; rank < BOARD_SIZE; ++rank) {
            for (int file = 0; file < BOARD_SIZE; ++file) {
                int x = file * SQUARE_SIZE;
                int y = rank * SQUARE_SIZE;

                SDL_Rect squareRect = {x, y, SQUARE_SIZE, SQUARE_SIZE};

                // Alternate between white and black squares
                if ((rank + file) % 2 == 0) {
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
                } else {
                    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); // Gray
                }

                SDL_RenderFillRect(renderer, &squareRect);
            }
        }

        // Update the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
