using namespace std;

#include <unordered_map>
#include "./include/board.h"

// TODO: need to make this as PieceType instead of int

const unordered_map<char, int> piecesToNum = {
    {'P', PAWN},
    {'N', KNIGHT},
    {'B', BISHOP},
    {'R', ROOK},
    {'Q', QUEEN},
    {'K', KING},

    {'p', -PAWN},
    {'n', -KNIGHT},
    {'b', -BISHOP},
    {'r', -ROOK},
    {'q', -QUEEN},
    {'k', -KING}};