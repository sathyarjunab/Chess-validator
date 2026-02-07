using namespace std;

#include "./../include/pieces/pawn.h"
#include "./../include/pieces/knight.h"

#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    cout << "Chess Validator Initialized\n";

    vector<vector<int>> board = {
        {4, 2, 3, 5, 6, 3, 2, 4},
        {1, 1, 1, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-4, -2, -3, -5, -6, -3, -2, -4}};

    vector<vector<int>> moves = pawnMovement(board, 6, 3, 7, 4, BLACK);
    vector<vector<int>> kmoves = knightMovement(board, 7, 1, 7, 4, BLACK);

    cout << "Pawn moves: " << endl;

    for (vector<int> move : moves)
    {
        cout << move[0] << "," << move[1] << endl;
    }

    cout << "Knight moves: " << endl;

    for (vector<int> move : kmoves)
    {
        cout << move[0] << "," << move[1] << endl;
    }

    return 0;
}
