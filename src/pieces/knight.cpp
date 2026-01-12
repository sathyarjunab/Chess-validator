using namespace std;

#include "./../../include/pieces/knight.h"
#include <vector>

// returns all valid L-shaped moves for a knight from (x, y) on the board
vector<vector<int>> lMovement(vector<vector<int>> &board, int x, int y)
{
    int rows = board.size();
    int cols = board[0].size();

    vector<vector<int>> moves;

    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};

    for (int i = 0; i < 8; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols)
        {
            moves.push_back({nx, ny});
        }
    }

    return moves;
}
