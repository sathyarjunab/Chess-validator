using namespace std;
// piece includes
#include "./include/pieces/pawn.h"
#include "./include/pieces/knight.h"
#include "./include/pieces/bishop.h"
#include "./include/pieces/rook.h"
#include "./include/pieces/queen.h"
#include "./include/helper/helper.h"
#include "./include/pieces/king.h"
#include "./include/main.h"

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
    return 0;
};

vector<string> giveMeMove(const string &fen, const string &pieceMove, const string &kingPosition)
{
    auto [x, y] = algebraicNotationToVector(pieceMove);
    auto [kx, ky] = algebraicNotationToVector(kingPosition);

    auto [board, activeColor, draw, whiteKingPosition, blackKingPosition, enPassant, castlingRights, pieceLocation] = FENToVector(fen);

    int enPassantX;
    int enPassantY;

    if (enPassant != "-")
    {
        CoOrdinates enPassantCoordinates = algebraicNotationToVector(enPassant);
        enPassantX = enPassantCoordinates.x;
        enPassantY = enPassantCoordinates.y;
    }

    if (draw)
    {
        return {"DRAW"};
    }

    // testing logging the complete board to check what it will give

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }

    cout << "given x,y" << x << " " << y << endl;
    cout << "en-Passant-co" << enPassantX << " " << enPassantY << endl;

    int piece = board[x][y];

    vector<int> attackerKingPosition = activeColor == WHITE ? blackKingPosition : whiteKingPosition;

    //  check if the king is in attack
    bool inCheck = isKingInCheck(board, kx, ky, activeColor);

    if (inCheck)
    {
        // if he is in attack lets check if some one as won
        result mate = checkForMate(board, kx, ky, activeColor, true, attackerKingPosition[0], attackerKingPosition[1]);

        cout << "came out of the checkmate function" << endl;

        if (mate.inCheckMate)
        {
            return {mate.whoWon == WHITE ? "WHITE WON" : "BLACK WON"};
        }
    }

    if (isBoardOnStalemate(pieceLocation, board, kx, ky, activeColor, enPassantX, enPassantY, castlingRights))
    {
        return {"STALEMATE"};
    }

    if (piece == EMPTY)
    {
        throw runtime_error("No piece at given square");
    }

    return pieceCaller(board, piece, x, y, kx, ky, activeColor, enPassantX, enPassantY, castlingRights);
}

vector<string> pieceCaller(vector<vector<int>> &board, int piece, int x, int y, int kx, int ky, Color activeColor, int enPassantX, int enPassantY, string castlingRights)
{
    vector<string> validAlgebraicNotation;

    int absPiece = abs(piece); // determines type of piece

    switch (absPiece)
    {
    case PAWN:
    {
        cout << "pawn" << endl;
        vector<vector<int>> validMoves = pawnMovement(board, x, y, kx, ky, activeColor, {enPassantX, enPassantY});
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case KNIGHT:
    {
        cout << "knight" << endl;
        vector<vector<int>> validMoves = knightMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case BISHOP:
    {
        cout << "bishop" << endl;
        vector<vector<int>> validMoves = bishopMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case ROOK:
    {
        cout << "rook" << endl;
        vector<vector<int>> validMoves = rookMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case QUEEN:
    {
        cout << "Queen" << endl;
        vector<vector<int>> validMoves = queenMovement(board, x, y, kx, ky, activeColor);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    case KING:
    {
        cout << "king" << endl;
        vector<vector<int>> validMoves = kingMovement(board, kx, ky, activeColor, castlingRights);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    default:
        throw runtime_error("Unknown piece type");
    };
    return validAlgebraicNotation;
}
