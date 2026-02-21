#ifndef BISHOP_H
#define BISHOP_H

#include <vector>
#include "./../board.h"

// Forward declaration if radialDirection is defined elsewhere
struct radialDirection;

// Calculates legal bishop moves from (x, y)
// Returns a list of safe destination squares
std::vector<std::vector<int>> bishopMovement(
    std::vector<std::vector<int>> &board,
    int x,
    int y,
    int kingX,
    int kingY,
    Color color);

#endif