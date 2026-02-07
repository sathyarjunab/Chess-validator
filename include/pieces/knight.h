#ifndef KNIGHT_CHECK_H
#define KNIGHT_CHECK_H

#include "./../board.h"

#include <vector>

using namespace std;

vector<vector<int>> lMovement(const vector<vector<int>> &board,
                              int X,
                              int Y);
vector<vector<int>> knightMovement(vector<vector<int>> &board,
                                   int X,
                                   int Y,
                                   int kingX,
                                   int kingY,
                                   Color color);

#endif
