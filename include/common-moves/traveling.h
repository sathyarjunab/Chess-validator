#ifndef RAY_SCAN_H
#define RAY_SCAN_H

using namespace std;

#include <vector>

enum Direction
{
    ORTHOGONAL = 'O',
    DIAGONAL = 'D',
    INVALID = 'I'
};

struct radialDirection
{
    int x;
    int y;
    int dx;
    int dy;
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

RayScanReturn rayScan(const vector<vector<int>> &board,
                      int x,
                      int y,
                      int dx,
                      int dy);

void rayScanFilter(vector<radialDirection> &validMoves, vector<vector<int>> &direction, vector<vector<int>> &board, int x, int y, Color color);

void rayMovementSquares(vector<vector<int>> &safeMoves, vector<radialDirection> &validMoves, vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color);

#endif
