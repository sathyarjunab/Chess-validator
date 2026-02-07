#ifndef KING_CHECK_H
#define KING_CHECK_H

#include <vector>
#include "./../board.h"

bool isKingInCheck(const vector<std::vector<int>> &board,
                   int kingX,
                   int kingY,
                   Color kingColor);

#endif
