cmake_minimum_required(VERSION 3.16)

project(ChessGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ChessGame
    src/main.cpp
    src/Knight.cpp
    src/Rook.cpp
    src/Bishop.cpp
    src/Queen.cpp
    src/King.cpp
    src/Pawn.cpp
    src/Board.cpp
    src/MoveValidator.cpp
)

target_include_directories(ChessGame
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)