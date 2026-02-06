using namespace std;

// .h file imports "./../../include/rules/"
#include "./../../include/common-moves/traveling.h"

using namespace std;

RayScanReturn rayScan(const vector<vector<int>> &board,
                      int x,
                      int y,
                      int dx,
                      int dy)
{
    int maxRow = board.size();
    int maxCol = board[0].size();

    int steps = 0;

    x += dx;
    y += dy;
    steps++;

    Direction direction = (dx == 0 || dy == 0) ? ORTHOGONAL : DIAGONAL;

    while (x >= 0 && x < maxRow && y >= 0 && y < maxCol)
    {
        if (board[x][y] != 0)
            return {x, y, steps, direction};

        x += dx;
        y += dy;
        steps++;
    }

    return {-1, -1, steps, direction};
}
