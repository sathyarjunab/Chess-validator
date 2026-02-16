using namespace std;

#include <iostream>
#include <stdio.h>
#include <vector>

#include "./../../include/board.h"
#include "./../../include/pieces/king.h"
#include "./../../include/common-moves/traveling.h"

vector<vector<int>> queenMovement(vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color)
{
    if (isKingInCheck(board, kingX, kingY, color))
    {
        // TODO: check if the game is over by checkmate or stalemate
    }

    vector<vector<int>> directions = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // orthogonal
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1} // diagonal
    };

    vector<radialDirection> validMoves;
    vector<vector<int>> safeMoves;

    rayScanHitReturn(board, validMoves, directions, x, y, color);

    if (validMoves.size() > 0)
    {
        rayMovementSquares(board, safeMoves, validMoves, x, y, kingX, kingY, color);
    }

    return safeMoves;
}