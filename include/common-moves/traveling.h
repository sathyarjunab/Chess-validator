#ifndef RAY_SCAN_H
#define RAY_SCAN_H

#include <vector>

enum Direction
{
    ORTHOGONAL = 'O',
    DIAGONAL = 'D',
};

struct RayScanReturn
{
    int x;
    int y;
    int steps;
    Direction direction;
};

RayScanReturn rayScan(const std::vector<std::vector<int>> &board,
                      int x,
                      int y,
                      int dx,
                      int dy);

#endif
