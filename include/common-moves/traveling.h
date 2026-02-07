#ifndef RAY_SCAN_H
#define RAY_SCAN_H

#include <vector>

enum Direction
{
    ORTHOGONAL = 'O',
    DIAGONAL = 'D',
    INVALID = 'I'
};

struct RayScanReturn
{
    int x;
    int y;
    int steps;
    Direction direction;
    int prevXIndex; // Added to store the last valid x index
    int prevYIndex; // Added to store the last valid y index
};

RayScanReturn rayScan(const std::vector<std::vector<int>> &board,
                      int x,
                      int y,
                      int dx,
                      int dy);

#endif
