#ifndef PAWN_H
#define PAWN_H

#include "./../board.h"

using namespace std;

#include <vector>

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
    Color color,
    vector<int> &enPassantCoordinates);

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
    int direction,
    vector<int> &enPassantCoordinates);

#endif // PAWN_H
