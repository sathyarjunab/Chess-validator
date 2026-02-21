using namespace std;
// piece includes
#include "./include/pieces/pawn.h"
#include "./include/pieces/knight.h"
#include "./include/pieces/king.h"
#include "./include/pieces/bishop.h"
#include "./include/pieces/rook.h"
#include "./include/pieces/queen.h"

#include "./include/helper/boardConvertor.h"

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    cout << "Chess Validator Initialized\n";

    vector<vector<int>> board = {
        {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK},
        {PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {-PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN},
        {-ROOK, -KNIGHT, -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK}};
    // resBoard data = FENToVector("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    // cout << data.board[0][0] << " " << data.board[0][1] << " " << data.board[0][2] << " " << data.board[0][3] << " " << data.board[0][4] << " " << data.board[0][5] << " " << data.board[0][6] << " " << data.board[0][7] << endl;

    return 0;
};

vector<string> giveMeMove(string &fen, string &pieceMove, string &kingPosition)
{
    auto [x, y] = algebraicNotationToVector(pieceMove);
    auto [kx, ky] = algebraicNotationToVector(kingPosition);

    cout << x << " " << y << "testing log" << endl;

    auto [board, activeColor, won] = FENToVector(fen);

    if (won)
    {
        return {"Game Over"};
    }

    // testing logging the complete board to check what it will give

    vector<string> validAlgebraicNotation;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    int piece = board[x][y];

    if (piece == EMPTY)
    {
        throw runtime_error("No piece at given square");
    }

    int absPiece = abs(piece); // determines type of piece

    switch (absPiece)
    {
    case PAWN:
    {
        vector<vector<int>> validMoves = pawnMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case KNIGHT:
    {
        vector<vector<int>> validMoves = knightMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case BISHOP:
    {
        vector<vector<int>> validMoves = bishopMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case ROOK:
    {
        vector<vector<int>> validMoves = rookMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case QUEEN:
    {
        vector<vector<int>> validMoves = queenMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case KING:
    {
        vector<vector<int>> validMoves = kingMovement(board, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    default:
        throw runtime_error("Unknown piece type");
    };

    return validAlgebraicNotation;
}
