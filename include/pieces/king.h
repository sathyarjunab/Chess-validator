#ifndef KING_CHECK_H
#define KING_CHECK_H

#include <vector>
#include <optional>
#include <string>

#include "./../board.h"

bool isKingInCheck(const vector<std::vector<int>> &board,
                   int kingX,
                   int kingY,
                   Color kingColor);

vector<vector<int>> kingMovement(vector<vector<int>> &board,
                                 int kingX,
                                 int kingY,
                                 Color kingColor,
                                 string castlingRights);

struct result
{
    bool inCheckMate;
    optional<Color> whoWon;
};

// Checks if the king at (kingX, kingY) of color kingColor is in checkmate
// board       : 8x8 board representation
// kingX, kingY: coordinates of the king
// kingColor   : color of the king (WHITE or BLACK)
// kingInCheck : optional, true if king is already known to be in check
// Returns true if the king is checkmated, false otherwise
result checkForMate(vector<vector<int>> &board, int kingX, int kingY, Color kingColor, bool kingInCheck, int opponentsKingX, int opponentsKingY);

#endif
