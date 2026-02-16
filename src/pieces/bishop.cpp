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
    vector<vector<int>> direction = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

    rayScanHitReturn(board, validMoves, direction, x, y, color);

    vector<vector<int>> safeMoves;

    rayMovementSquares(board, safeMoves, validMoves, x, y, kingX, kingY, color);

    return safeMoves;
}