using namespace std;

#include "./../include/pieces/pawn.h"
#include "./../include/pieces/knight.h"
#include "./../include/pieces/king.h"

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

    vector<vector<int>> moves = pawnMovement(board, 6, 3, 7, 4, BLACK);
    vector<vector<int>> kmoves = knightMovement(board, 7, 1, 7, 4, BLACK);
    // bool isKing = isKingInCheck(board, 7, 4, BLACK);

    return 0;
}
