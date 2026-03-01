using namespace std;

#include <unordered_map>

#include "./include/board.h"
#include "./include/main.h"

// TODO: need to make this as PieceType instead of int

const unordered_map<char, int> piecesToNum = {
    {'P', PAWN},
    {'N', KNIGHT},
    {'B', BISHOP},
    {'R', ROOK},
    {'Q', QUEEN},
    {'K', KING},

    {'p', -PAWN},
    {'n', -KNIGHT},
    {'b', -BISHOP},
    {'r', -ROOK},
    {'q', -QUEEN},
    {'k', -KING}};

bool isBoardOnStalemate(vector<vector<int>> &pieceLocation, vector<vector<int>> &board, int kx, int ky, Color activeColor, int enPassantX, int enPassantY, string castlingRights)
{
    for (const auto &piece : pieceLocation)
    {
        vector<string> validMoves = pieceCaller(board, piece[0], piece[1], piece[2], kx, ky, activeColor, enPassantX, enPassantY, castlingRights);
        if (validMoves.size() > 0)
        {
            return false;
        }
    }
    return true;
}
