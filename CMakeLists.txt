cmake_minimum_required(VERSION 3.16)

project(ChessLibrary)

set(CMAKE_CXX_STANDARD 11)

include_directories(src/includes)

# Add source files
set(SOURCES
    src/includes/board.h
    src/includes/structs.h
    src/includes/board_utils.h
    src/includes/pieces.h
    src/includes/notation.h
    src/includes/movement.h


    src/Board/board_utils.cpp
    src/Board/Board.cpp
    src/Board/special_piece_moves.cpp
    src/Board/king_checks.cpp
    src/Board/movement.cpp
    
    src/Pieces/Bishop.cpp
    src/Pieces/King.cpp
    src/Pieces/Knight.cpp
    src/Pieces/Pawn.cpp
    src/Pieces/Piece.cpp
    src/Pieces/Pieces.cpp
    src/Pieces/Queen.cpp
    src/Pieces/Rook.cpp
    
    src/Notation/fen.cpp
    src/Notation/pgn.cpp

)


# add_executable(Chess ${SOURCES})
add_library(ChessLibrary ${SOURCES})

