#ifndef RAY_SCAN_H
#define RAY_SCAN_H

using namespace std;

#include "./../board.h"

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

void rayScanHitReturn(vector<vector<int>> &board, vector<radialDirection> &validMoves, vector<vector<int>> &direction, int x, int y, Color color);

void rayMovementSquares(vector<vector<int>> &board, vector<vector<int>> &safeMoves, vector<radialDirection> &validMoves, int x, int y, int kingX, int kingY, Color color);

#endif
