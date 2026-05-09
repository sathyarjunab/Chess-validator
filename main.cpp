using namespace std;
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

    int piece = board[x][y];

    vector<int> attackerKingPosition = activeColor == WHITE ? blackKingPosition : whiteKingPosition;

    //  check if the king is in attack
    bool inCheck = isKingInCheck(board, kx, ky, activeColor);

    if (inCheck)
    {
        // if he is in attack lets check if some one as won
        result mate = checkForMate(board, kx, ky, activeColor, true, attackerKingPosition[0], attackerKingPosition[1]);

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
        vector<vector<int>> validMoves = pawnMovement(board, x, y, kx, ky, activeColor, {enPassantX, enPassantY});
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
        vector<vector<int>> validMoves = kingMovement(board, kx, ky, activeColor, castlingRights);
        validAlgebraicNotation = vectorToAlgebraicNotation(validMoves);
        break;
    }

    default:
        throw runtime_error("Unknown piece type");
    };
    return validAlgebraicNotation;
}
