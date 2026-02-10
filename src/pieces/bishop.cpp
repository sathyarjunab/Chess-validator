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

    rayScanFilter(validMoves, direction, board, x, y, color);

    vector<vector<int>> safeMoves;

    rayMovementSquares(safeMoves, validMoves, board, )

        return safeMoves;
}