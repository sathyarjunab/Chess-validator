using namespace std;

#include "./../../include/pieces/pawn.h"
#include "./../../include/pieces/king.h"

#include <stdio.h>
#include <iostream>
#include <vector>

vector<vector<int>> pawnMovement(vector<vector<int>> &board, int x, int y, int kingX, int kingY, int color)
{

    vector<vector<int>> validMoves;
    if (isKingInCheck(board, kingX, kingY, color))
    {
        // check if the pawn clicked can block the check
        // check if the game is over
    }

    int left = y - 1;
    int right = y + 1;
    // white
    if (color > 0)
    {
        int dx = x + 1;

        if (dx < board.size())
        {
            vector<vector<int>> boardCopy = board;

            boardCopy[dx][left] = board[x][y];
            boardCopy[x][y] = 0;
            if (board[dx][left] <= 0 && !isKingInCheck(boardCopy, kingX, kingY, color))
            {
                validMoves.push_back({dx, left});
            }
            boardCopy[dx][left] = board[dx][left];
            boardCopy[x][y] = board[x][y];

            boardCopy[dx][right] = board[dx][left];
            boardCopy[x][y] = board[x][y];
            if (board[dx][right] <= 0 && !isKingInCheck(boardCopy, kingX, kingY, color))
            {
                validMoves.push_back({dx, right});
            }
        }
        else
        {
            int dx = x - 1;

            if (dx >= 0)
            {
                vector<vector<int>> boardCopy = board;

                boardCopy[dx][left] = board[x][y];
                boardCopy[x][y] = 0;
                if (board[dx][left] <= 0 && !isKingInCheck(boardCopy, kingX, kingY, color))
                {
                    validMoves.push_back({dx, left});
                }
            }
        }
    }
    else
    {
    }
}
