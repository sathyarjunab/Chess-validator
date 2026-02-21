#ifndef QUEEN_H
#define QUEEN_H

#include <vector>
#include "./../board.h"

// Forward declaration (defined in traveling.h)
struct radialDirection;

// Calculates legal queen moves from (x, y)
// Returns safe destination squares
std::vector<std::vector<int>> queenMovement(
    std::vector<std::vector<int>> &board,
    int x,
    int y,
    int kingX,
    int kingY,
    Color color);

#endif