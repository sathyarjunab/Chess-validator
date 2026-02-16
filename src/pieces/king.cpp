using namespace std;

// .h file imports "./../../include/pieces/"
#include "./../../include/pieces/king.h"
#include "./../../include/common-moves/traveling.h"
#include "./../../include/pieces/knight.h"
#include "./../../include/board.h"

bool isKingInCheck(const vector<vector<int>> &board,
                   int kingX,
                   int kingY,
                   Color kingColor)
{

    // gives all the L-shaped moves
    vector<vector<int>> moves = lMovement(board, kingX, kingY);

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
        RayScanReturn hit = rayScan(board, kingX, kingY, d[0], d[1]);

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
        int x = kingX + 1;
        if (x < board.size())
        {
            if (kingY > 0 && board[x][kingY - 1] == -PAWN)
                return true;
            if (kingY < board[0].size() && board[x][kingY + 1] == -PAWN)
                return true;
        }
    }
    else
    {

        int x = kingX - 1;
        if (x > 0)
        {
            if (kingY > 0 && board[x][kingY - 1] == PAWN)
                return true;
            if (kingY < board[0].size() && board[x][kingY + 1] == PAWN)
                return true;
        }
    }

    return false;
}

vector<vector<int>> kingMovement(vector<vector<int>> &board,
                                 int kingX,
                                 int kingY,
                                 Color kingColor,
                                 bool kingMoved)
{

    vector<vector<int>> possibleDirection = {
        {-1, 0},
        {1, 0},
        {0, 1},
        {0, -1},
        {-1, 1},
        {-1, -1},
        {1, 1},
        {1, -1},
    };

    if (!kingMoved)
    {
        int x = kingColor == WHITE ? 0 : 7;
        int y = 4;

        // possibleDirection.push_back({x,})
        // both long castling and short castling should be implemented
    }

    vector<vector<int>> validMoves;

    for (const vector<int> &moves : possibleDirection)
    {
        int mX = kingX + moves[0];
        int mY = kingY + moves[1];

        if (mX < 0 || mX >= board.size() || mY < 0 || mY >= board[0].size())
            continue;

        if ((board[mX][mY] > 0 && kingColor == WHITE) || (board[mX][mY] < 0 && kingColor == BLACK))
            continue;

        // check if, if you make the current move, does that move bring the king to check.

        int temp = board[mX][mY];
        board[mX][mY] = board[kingX][kingY];
        board[kingX][kingY] = EMPTY;
        if (isKingInCheck(board, mX, mY, kingColor))
            continue;

        board[kingX][kingY] = board[mX][mY];
        board[mX][mY] = temp;

        validMoves.push_back({mX, mY});
    }

    return validMoves;
}
