cmake_minimum_required(VERSION 3.16)

project(ChessLibrary)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

include(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

# Add source files
set(SOURCES
    src/main.cpp
    src/chess_lib.h

    src/Board/board_utils.cpp
    src/Board/board_utils.h
    src/Board/Board.cpp
    src/Board/board.h
    src/Board/special_piece_moves.cpp
    src/Board/king_checks.cpp
    src/Board/movement.cpp
    src/Board/structs.h
    
    src/Game/game_logic.cpp
    src/Game/game_logic.h
    src/Game/game_utils.h
    
    
    src/Pieces/Bishop.cpp
    src/Pieces/King.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/Pieces.h
    src/Pieces/Piece.cpp
    src/Pieces/Pieces.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Rook.cpp
    
    src/Notation/fen.cpp
    src/Notation/pgn.cpp
    src/Notation/notation.h

)

set(TESTS
    tests/tests.h
    tests/test_fens.h
    tests/tests.cpp
)

add_executable(Chess ${SOURCES} ${TESTS})
# add_library(Chess ${SOURCES} ${TESTS})

