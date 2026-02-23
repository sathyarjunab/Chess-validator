using namespace std;

#include <stdexcept>
#include <stdio.h>
#include <iostream>
#include <stdexcept>

#include "./../include/helper/helper.h"
#include "./../include/common-moves/traveling.h"
#include "./../include/pieces/knight.h"
#include "./../include/board.h"
#include "./../include/helper/helper.h"
#include "./../include/pieces/king.h"

// WARNING: never call isAttacked function inside this function
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
            if (kingY < board[0].size() - 1 && board[x][kingY + 1] == -PAWN)
                return true;
        }
    }
    else
    {

        int x = kingX - 1;
        if (x >= 0)
        {
            if (kingY > 0 && board[x][kingY - 1] == PAWN)
                return true;
            if (kingY < board[0].size() - 1 && board[x][kingY + 1] == PAWN)
                return true;
        }
    }

    // need to check if the king is attacked by the king itself

    static const int kingDirections[8][2] = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    for (auto &d : kingDirections)
    {
        int nx = kingX + d[0];
        int ny = kingY + d[1];

        if (nx < 0 || nx > 7 || ny < 0 || ny > 7)
            continue;
        int piece = board[nx][ny];

        if ((kingColor == BLACK && piece == KING) ||
            (kingColor == WHITE && piece == -KING))
            return true;
    }

    return false;
}

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

    // WARN: was commented out for a reason do not remove
    //  if (!kingMoved)
    //  {
    //      int x = kingColor == WHITE ? 0 : 7;
    //      int y = 4;

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
        bool inCheck = isKingInCheck(board, mX, mY, kingColor);
        board[kingX][kingY] = board[mX][mY];
        board[mX][mY] = temp;

        if (inCheck)
            continue;

        validMoves.push_back({mX, mY});
    }

    return validMoves;
}

result checkForMate(vector<vector<int>> &board, int kingX, int kingY, Color kingColor, bool kingInCheck, int opponentsKingX, int opponentsKingY)
{
    try
    {
        Color opponentColor = kingColor == WHITE ? BLACK : WHITE;

        AttackerReturn kingAttackInfo = isAttacked(board, kingX, kingY, kingColor, false);

        if (!kingAttackInfo.isInAttack)
            return {false, {}};

        // lets see if there are any legal moves for king if yes then no one has won

        vector<vector<int>> moves = kingMovement(board, kingX, kingY, kingColor);
        // since there are legal moves available then no one has won
        if (moves.size() > 0)
            return {false, {}};

        // the only way king could have saved from this check was by moving itself to a square that is not under attack
        // and since that is not possible then the king is checkmated

        if (kingAttackInfo.numberOfAttacks >= 2)
        {
            return {true, opponentColor};
        }

        // if there is only one attack then we could save the king by two ways

        // 1. take the piece that is attacking the king
        AttackerReturn isHunterBeingHunted = isAttacked(board, kingAttackInfo.attackers[0].x, kingAttackInfo.attackers[0].y, opponentColor, false);

        // TODO: before taking the piece that is attacking the king, check if the king will come under attack again because of this move

        if (isHunterBeingHunted.isInAttack && kingAttackInfo.attackers.size() >= 1)
        {
            return {false, {}};
        }
        // 2. block the piece that is attacking the king

        // 2.1 get the direction in which the king is been attacked,
        // NOTE: there can be no way king and the opponent piece be present next to each other without a empty space in between

        AttackerDetails attackerDetail = kingAttackInfo.attackers[0];

        vector<int> d = attackerDetail.direction;

        int attemptX = attackerDetail.x + d[0];

        int attemptY = attackerDetail.y + d[1];

        while ((attemptX != attackerDetail.x || attemptY != attackerDetail.y) && (attemptX < attackerDetail.x && attemptY < attackerDetail.y))
        {
            if (attemptX < 0 || attemptX > 7 || attemptY < 0 || attemptY > 7)
                throw runtime_error("Went out of bound while checking for mate");

            AttackerReturn lastHopes = isAttacked(board, attemptX, attemptY, opponentColor, false);

            vector<AttackerDetails> legalMoves = legallyAttacked(board, attemptX, attemptY, opponentColor, opponentsKingX, opponentsKingY, lastHopes.attackers);

            if (legalMoves.size() > 0)
                return {false, {}};

            attemptX = attackerDetail.x + d[0];
            attemptY = attackerDetail.y + d[1];
        }

        return {true, opponentColor};
    }
    catch (runtime_error e)
    {
        cout << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "something went wrong" << endl;
    }
}
