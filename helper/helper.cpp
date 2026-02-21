using namespace std;

#include <iostream>
#include <stdio.h>
#include <vector>

#include "./../include/board.h"
#include "./../include/pieces/knight.h"
#include "./../include/common-moves/traveling.h"

bool isAttacked(const vector<vector<int>> &board,
                int x,
                int y,
                Color kingColor)
{

    // gives all the L-shaped moves
    vector<vector<int>> moves = lMovement(board, x, y);

    // Check for knight attacks
    for (vector<int> move : moves)
    {
        int x = move[0];
        int y = move[1];

        if (kingColor == BLACK && board[x][y] == KNIGHT)
        {
            return true;
        }

        if (kingColor == WHITE && board[x][y] == -KNIGHT)
        {
            return true;
        }
    }

    // Rook / Queen directions
    int directions[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, // orthogonal
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1} // diagonal
    };

    for (const auto &d : directions)
    {
        RayScanReturn hit = rayScan(board, x, y, d[0], d[1]);

        if (hit.x == -1)
            continue;

        int piece = board[hit.x][hit.y];

        // opponent piece only
        if ((piece > 0 && kingColor == BLACK) || (piece < 0 && kingColor == WHITE))
        {
            int absPiece = abs(piece);

            // rook or queen
            if ((d[0] == 0 || d[1] == 0) && (absPiece == ROOK || absPiece == QUEEN))
                return true;

            // bishop or queen
            if ((d[0] != 0 && d[1] != 0) && (absPiece == BISHOP || absPiece == QUEEN))
                return true;
        }
    }

    // pawn attack
    if (kingColor == WHITE)
    {
        int x = x + 1;
        if (x < board.size())
        {
            if (y > 0 && board[x][y - 1] == -PAWN)
                return true;
            if (y < board[0].size() && board[x][y + 1] == -PAWN)
                return true;
        }
    }
    else
    {

        int x = x - 1;
        if (x > 0)
        {
            if (y > 0 && board[x][y - 1] == PAWN)
                return true;
            if (y < board[0].size() && board[x][y + 1] == PAWN)
                return true;
        }
    }

    return false;
}
