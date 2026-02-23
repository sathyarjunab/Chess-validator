using namespace std;

#include <iostream>
#include <stdio.h>
#include <vector>

#include "./../include/board.h"
#include "./../include/pieces/knight.h"
#include "./../include/pieces/king.h"
#include "./../include/common-moves/traveling.h"
#include "./../include/helper/helper.h"

bool isLegalAttackMove(vector<vector<int>> &board,
                       int fromX, int fromY,
                       int toX, int toY,
                       int opponentsKingX, int opponentsKingY,
                       Color opponentColor)
{
    int captured = board[toX][toY];
    int piece = board[fromX][fromY];

    board[toX][toY] = piece;
    board[fromX][fromY] = EMPTY;

    bool inCheck = isKingInCheck(board, opponentsKingX, opponentsKingY, opponentColor);

    board[fromX][fromY] = piece;
    board[toX][toY] = captured;

    return !inCheck;
}

AttackerReturn isAttacked(vector<vector<int>> &board,
                          int x,
                          int y,
                          Color pieceColor,
                          bool wantToCheckKingAttack = true)
{

    int numberOfAttackers = 0;
    vector<AttackerDetails> attacker;
    // gives all the L-shaped moves
    vector<vector<int>> moves = lMovement(board, x, y);
    Color opponentColor = pieceColor == BLACK ? WHITE : BLACK;

    // Check for knight attacks
    for (vector<int> &move : moves)
    {
        int aX = move[0];
        int aY = move[1];

        if ((pieceColor == BLACK && board[aX][aY] == KNIGHT) || (pieceColor == WHITE && board[aX][aY] == -KNIGHT))
        {
            numberOfAttackers++;
            attacker.push_back({aX, aY, {}});
        }
    }

    cout << "1." << numberOfAttackers << endl;

    // Rook / Queen directions
    static const int directions[8][2] = {
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
        if ((piece > 0 && pieceColor == BLACK) || (piece < 0 && pieceColor == WHITE))
        {
            int absPiece = abs(piece);
            // rook,bishop or queen
            if (((d[0] == 0 || d[1] == 0) && (absPiece == ROOK || absPiece == QUEEN)) || ((d[0] != 0 && d[1] != 0) && (absPiece == BISHOP || absPiece == QUEEN)))
            {
                numberOfAttackers++;
                attacker.push_back({hit.x, hit.y, {d[0], d[1]}});
            }
        }
    }

    cout << "2." << numberOfAttackers << endl;

    // pawn attack
    if (pieceColor == WHITE)
    {
        int X = x + 1;
        if (X < board.size())
        {
            if (y > 0 && board[X][y - 1] == -PAWN)
            {
                numberOfAttackers++;
                attacker.push_back({X, y - 1, {1, -1}});
            }
            if (y < board[0].size() - 1 && board[X][y + 1] == -PAWN)
            {
                numberOfAttackers++;
                attacker.push_back({X, y + 1, {1, 1}});
            }
        }
    }
    else
    {

        int X = x - 1;
        if (X >= 0)
        {
            if (y > 0 && board[X][y - 1] == PAWN)
            {
                numberOfAttackers++;
                attacker.push_back({X, y - 1, {-1, -1}});
            }
            if (y < board[0].size() - 1 && board[X][y + 1] == PAWN)
            {
                numberOfAttackers++;
                attacker.push_back({X, y + 1, {-1, 1}});
            }
        }
    }

    cout << "3." << numberOfAttackers << endl;

    if (wantToCheckKingAttack)
    {
        static const int directions[8][2] = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        for (auto &d : directions)
        {
            int nx = x + d[0];
            int ny = y + d[1];

            if (nx < 0 || nx > 7 || ny < 0 || ny > 7)
                continue;
            int piece = board[nx][ny];

            if ((pieceColor == WHITE && piece < 0 && abs(piece) == KING) ||
                (pieceColor == BLACK && piece > 0 && abs(piece) == KING))
            {
                numberOfAttackers++;
                attacker.push_back({nx, ny, {d[0], d[1]}});
            }
        }
    }
    cout << "4." << numberOfAttackers << endl;

    if (numberOfAttackers == 0)
    {
        cout << "where is it ";
        return {false, numberOfAttackers, attacker};
    }
    else
    {
        cout << "where is it ";
        return {true, numberOfAttackers, attacker};
    }
}

vector<AttackerDetails> legallyAttacked(vector<vector<int>> &board,
                                        int x,
                                        int y,
                                        Color pieceColor,
                                        int opponentsKingX,
                                        int opponentsKingY,
                                        vector<AttackerDetails> &attackersList)
{

    Color opponentColor = pieceColor == WHITE ? BLACK : WHITE;
    vector<AttackerDetails> legalAttacker;

    for (AttackerDetails &attacker : attackersList)
    {
        int fromX = attacker.x;
        int fromY = attacker.y;

        bool isLegalAttack = isLegalAttackMove(board, fromX, fromY, x, y, opponentsKingX, opponentsKingY, opponentColor);

        if (isLegalAttack)
        {
            legalAttacker.push_back(attacker);
        }
    }
    return legalAttacker;
}