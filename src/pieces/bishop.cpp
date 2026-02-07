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
    int direction[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

    // Loop through each diagonal direction and perform ray scanning
    for (const auto &d : direction)
    {
        RayScanReturn hit = rayScan(board, x, y, d[0], d[1]);

        int dx = hit.x;
        int dy = hit.y;

        if ((dx >= 0 && dx < board.size() && dy >= 0 && dy < board[0].size()))
        {
            if (board[dx][dy] > 0 && color == BLACK || board[dx][dy] < 0 && color == WHITE)
            {
                validMoves.push_back({dx, dy, d[0], d[1]});
            }
            else
            {
                validMoves.push_back({hit.prevXIndex, hit.prevYIndex, d[0], d[1]});
            }
        }
        else
        {
            // No piece found in this direction, so we can move there
            validMoves.push_back({hit.prevXIndex, hit.prevYIndex, d[0], d[1]});
        }
    }

    vector<vector<int>> safeMoves;

    // Loop through each valid move and check if it puts the king in check
    for (radialDirection move : validMoves)
    {
        int cX = x;
        int cY = y;
        bool shouldBreak = false;

        while (cX + move.dx >= 0 && cX + move.dx < 8 && cY + move.dy >= 0 && cY + move.dy < 8)
        {

            cX += move.dx;
            cY += move.dy;

            vector<vector<int>> copyBoard = board;
            copyBoard[cX][cY] = board[x][y];
            copyBoard[x][y] = 0;

            if (!isKingInCheck(copyBoard, kingX, kingY, color))
            {
                safeMoves.push_back({cX, cY});
            }
            if ((cX == move.x && cY == move.y) || board[cX][cY] != 0)
            {
                break;
            }
        }
    }

    return safeMoves;
}