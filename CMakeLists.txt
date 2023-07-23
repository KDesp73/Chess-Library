cmake_minimum_required(VERSION 3.16)

project(ChessLibrary)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

# Add source files
set(SOURCES
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

set(HEADERS
    include/board.h
    include/structs.h
    include/board_utils.h
    include/pieces.h
    include/notation.h
    include/movement.h

    chess_lib.h
)

# add_executable(Chess ${SOURCES})
add_library(ChessLibrary ${SOURCES} ${HEADERS})

