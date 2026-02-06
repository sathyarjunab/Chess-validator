#ifndef PAWN_H
#define PAWN_H

using namespace std;

#include <vector>

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

/**
 * Returns all valid pawn moves for a pawn at (x, y),
 * considering king safety.
 */
vector<vector<int>> pawnMovement(
    vector<vector<int>> &board,
    int x,
    int y,
    int kingX,
    int kingY,
    Color color);

/**
 * Internal helper to validate pawn moves
 * based on direction and king safety.
 */
vector<vector<int>> pawnValidMovesChecker(
    vector<vector<int>> &board,
    int x,
    int y,
    int kingX,
    int kingY,
    Color color,
    int direction);

#endif // PAWN_H
