#ifndef ROOK_H
#define ROOK_H

#include <vector>
#include "./../board.h"

// Forward declaration (defined in traveling.h or related header)
struct radialDirection;

// Calculates legal rook moves from (x, y)
// Returns safe destination squares
std::vector<std::vector<int>> rookMovement(
    std::vector<std::vector<int>> &board,
    int x,
    int y,
    int kingX,
    int kingY,
    Color color);

#endif