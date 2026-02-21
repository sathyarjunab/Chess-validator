#ifndef KING_CHECK_H
#define KING_CHECK_H

#include <vector>

#include "./../board.h"

vector<vector<int>> kingMovement(vector<vector<int>> &board,
                                 int kingX,
                                 int kingY,
                                 Color kingColor);

#endif
