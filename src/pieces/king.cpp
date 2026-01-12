using namespace std;

// .h file imports "./../../include/pieces/"
#include "./../../include/pieces/king.h"
#include "./../../include/common-moves/traveling.h"
#include "./../../include/pieces/knight.h"

bool isKingInCheck(const vector<vector<int>> &board,
                   int kingX,
                   int kingY,
                   int kingColor)
{

    // gives all the
    vector<vector<int>> moves = lMovement(board, kingX, kingY);

    // Check for knight attacks
    for (vector<int> move : moves)
    {
        int x = move[0];
        int y = move[1];

        if (kingColor < 0 && board[x][y] == 2)
        {
            return true;
        }

        if (kingColor > 0 && board[x][y] == -2)
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

    for (auto &d : directions)
    {
        RayScanReturn hit = rayScan(board, kingX, kingY, kingColor, d[0], d[1]);

        if (hit.x == -1)
            continue;

        int piece = board[hit.x][hit.y];

        // opponent piece only
        if ((piece > 0 && kingColor < 0) || (piece < 0 && kingColor > 0))
        {
            int absPiece = abs(piece);

            // rook or queen
            if ((d[0] == 0 || d[1] == 0) && (absPiece == 4 || absPiece == 5))
                return true;

            // bishop or queen
            if ((d[0] != 0 && d[1] != 0) && (absPiece == 3 || absPiece == 5))
                return true;

            // pawn attack
            if (abs(piece) == 1 && hit.steps == 1 && (d[0] != 0 && d[1] != 0))
            {
                if (kingColor > 0 && kingX > hit.x && piece == -1)
                    return true;
                if (kingColor < 0 && kingX < hit.x && piece == 1)
                    return true;
            }
        }
    }

    return false;
}
