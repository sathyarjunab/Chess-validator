#ifndef KING_CHECK_H
#define KING_CHECK_H

#include <vector>

bool isKingInCheck(const std::vector<std::vector<int>>& board,
                   int kingX,
                   int kingY,
                   int kingColor);

#endif
