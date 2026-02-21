using namespace std;

#include "./../include/helper/helper.h"
#include "./../include/common-moves/traveling.h"
#include "./../include/pieces/knight.h"
#include "./../include/board.h"
#include "./../include/helper/helper.h"

vector<vector<int>> kingMovement(vector<vector<int>> &board,
                                 int kingX,
                                 int kingY,
                                 Color kingColor)
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

    // if (!kingMoved)
    // {
    //     int x = kingColor == WHITE ? 0 : 7;
    //     int y = 4;

    // possibleDirection.push_back({x,})
    // both long castling and short castling should be implemented
    // }

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
        if (isAttacked(board, mX, mY, kingColor))
            continue;

        board[kingX][kingY] = board[mX][mY];
        board[mX][mY] = temp;

        validMoves.push_back({mX, mY});
    }

    return validMoves;
}

bool isKingInCheckMate(vector<vector<int>> &board, int kingX, int kingY, Color kingColor, bool kingInCheck = false)
{
    if (!kingInCheck && !isAttacked(board, kingX, kingY, kingColor))
    {
        return false;
    }
}