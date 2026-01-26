#ifndef RAY_SCAN_H
#define RAY_SCAN_H

#include <vector>

struct RayScanReturn
{
    int x;
    int y;
    int steps;
    char direction;
};

RayScanReturn rayScan(const std::vector<std::vector<int>> &board,
                      int x,
                      int y,
                      int color,
                      int dx,
                      int dy);

#endif
