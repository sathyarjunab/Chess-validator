#pragma once

#include <unordered_map>

/*
Color mapping:
WHITE =  1
BLACK = -1
*/
enum Color
{
    WHITE = 1,
    BLACK = -1
};

enum PieceType
{
    EMPTY = 0,
    PAWN = 1,
    KNIGHT = 2,
    BISHOP = 3,
    ROOK = 4,
    QUEEN = 5,
    KING = 6
};

// Only declare in header
extern const std::unordered_map<char, int> piecesToNum;