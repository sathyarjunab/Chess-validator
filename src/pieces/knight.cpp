using namespace std;

#include "./../../include/pieces/knight.h"
#include "./../../include/pieces/king.h"
#include "./../../include/board.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

// returns all valid L-shaped moves for a knight from (x, y) on the board
vector<vector<int>> lMovement(const vector<vector<int>> &board, int x, int y)
{
    int rows = board.size();
    int cols = board[0].size();

    vector<vector<int>> moves;

    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
        {
            moves.push_back({nx, ny});
        }
    }

    return moves;
}

vector<vector<int>> knightMovement(vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color)
{
    vector<vector<int>> validMoves;
    if (isKingInCheck(board, kingX, kingY, color))
    {
        // check if the game is over by checkmate or stalemate
    }
    // else then we can calculate the valid moves for the knight

    vector<vector<int>> possibleMoves = lMovement(board, x, y);

    vector<vector<int>> knightMoves;

    for (vector<int> move : possibleMoves)
    {
        int dx = move[0];
        int dy = move[1];

        if (board[dx][dy] == EMPTY || (board[dx][dy] > 0 && color == BLACK) || (board[dx][dy] < 0 && color == WHITE))
        {
            vector<vector<int>> copyBoard = board;
            copyBoard[dx][dy] = board[x][y];
            copyBoard[x][y] = EMPTY;
            if (isKingInCheck(copyBoard, kingX, kingY, color))
            {
                continue;
            }
            else
            {
                knightMoves.push_back(move);
            }
        }
    }
    return knightMoves;
}