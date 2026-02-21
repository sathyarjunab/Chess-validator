using namespace std;

#include "./../include/common-moves/traveling.h"
#include "./../include/board.h"
#include "./../include/pieces/king.h"

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>

vector<vector<int>> bishopMovement(vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color)
{

    if (isKingInCheck(board, kingX, kingY, color))
    {
        // check if the game is over by checkmate or stalemate
    }
    // else then we can calculate the valid moves for the bishop

    vector<radialDirection> validMoves;
    vector<vector<int>> safeMoves;
    vector<vector<int>> directions = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

    rayScanHitReturn(board, validMoves, directions, x, y, color);

    if (validMoves.size() > 0)
    {
        rayMovementSquares(board, safeMoves, validMoves, x, y, kingX, kingY, color);
    }

    return safeMoves;
}