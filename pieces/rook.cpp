using namespace std;

#include <iostream>
#include <stdio.h>
#include <vector>

#include "./../include/board.h"
#include "./../include/pieces/king.h"
#include "./../include/common-moves/traveling.h"

vector<vector<int>> rookMovement(vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color)
{
    if (isKingInCheck(board, kingX, kingY, color))
    {
        // TODO: check if the match as been won by the opponent by checkmate or its a stalemate
    }

    vector<vector<int>> direction = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1},
    };

    vector<radialDirection> validMoves;
    vector<vector<int>> safeMoves;

    rayScanHitReturn(board, validMoves, direction, x, y, color);

    if (validMoves.size() > 0)
    {
        rayMovementSquares(board, safeMoves, validMoves, x, y, kingX, kingY, color);
    }

    return safeMoves;
}