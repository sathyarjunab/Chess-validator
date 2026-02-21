using namespace std;

#include "./../include/pieces/pawn.h"
#include "./../include/pieces/king.h"
#include "./../include/helper/helper.h"
#include "./../include/helper/helper.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

// color == 1 is white
// color == -1 is black
// top white
// bottom black

// TODO: HANDLE PROMOTION AND EN PASSANT
// TODO: CHECK IF SOME ONE AS WON THE GAME BY CHECKMATE
// TODO: HANDLE STALEMATE

vector<vector<int>> pawnMovement(vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color)
{

    vector<vector<int>> validMoves;
    if (isAttacked(board, kingX, kingY, color))
    {
        // check if the game is over by checkmate or stalemate
    }
    // else then we can calculate the valid moves for the pawn

    int left = y - 1;
    int right = y + 1;

    if (color == WHITE && x == 0)
    {
        return validMoves;
    }
    if (color == BLACK && x == board.size() - 1)
    {
        return validMoves;
    }

    int direction;
    if (color == WHITE)
    {
        // If the pawn is white
        direction = 1;
    }
    else
    {
        // if the pawn is black
        direction = -1;
    }

    return pawnValidMovesChecker(board, x, y, kingX, kingY, color, direction);
}

// This function checks the valid moves for a pawn and also checks if the move puts the king in check
vector<vector<int>> pawnValidMovesChecker(vector<vector<int>> &board, int x, int y, int kingX, int kingY, Color color, int direction)
{
    vector<vector<int>> validMoves;
    vector<vector<int>> possibleMoves = {{x + (1 * direction), y}, {x + (2 * direction), y}, {x + direction, y - 1}, {x + direction, y + 1}};

    copy_if(possibleMoves.begin(), possibleMoves.end(), back_inserter(validMoves), [&board, color, y, x, direction, kingX, kingY](const vector<int> &coOrdinates)
            {
                // 1. check if the move is out of bounds
                // 2. check if the pawn is in the starting position and can move 2 steps
                // 3. check if the pwn is blocked to move in straight line for both one and two steps
                // 4. check if the pawn can capture an opponent piece diagonally
                // 5. allow the move if it is valid and does not put the king in check
                int dx = coOrdinates[0];
                int dy = coOrdinates[1];

                // 1. out of bound check 
                if (dx < 0 || dx >= board.size() || dy < 0 || dy >= board[0].size())
                {
                    return false;
                }

                bool isTwoSteps = abs(dx - x) == 2;
                bool canMoveOneStep = board[x + direction][y] == EMPTY;
                bool isOpposite = false;
                isOpposite = (board[dx][dy] > 0 && color == BLACK) || (board[dx][dy] < 0 && color == WHITE) ;


                // if it is straight move
                if (dy == y)
                {
                    if (isTwoSteps)
                    {
                        return canMoveOneStep && board[dx][dy] == EMPTY && ((color == WHITE && x == 1) || (color == BLACK && x == board.size() - 2));
                    }
                    else
                    {
                        return canMoveOneStep && board[dx][dy] == EMPTY;
                    }
                }
                else
                {
                    return isOpposite && abs(dy - y) == 1 && abs(dx - x) == 1;
                }
                
                return false; });

    vector<vector<int>> filteredMoves;
    copy_if(validMoves.begin(), validMoves.end(), back_inserter(filteredMoves), [&board, color, x, y, kingX, kingY](const vector<int> &move)
            {
        int dx = move[0];
        int dy = move[1];
        vector<vector<int>> boardCopy = board;
        boardCopy[dx][dy] = board[x][y];
        boardCopy[x][y] = EMPTY;

        return !isAttacked(boardCopy, kingX, kingY, color); });

    return filteredMoves;
}
