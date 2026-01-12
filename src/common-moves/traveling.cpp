using namespace std;

// .h file imports "./../../include/rules/"
#include "./../../include/common-moves/traveling.h"

using namespace std;

RayScanReturn rayScan(const vector<vector<int>> &board,
                      int x,
                      int y,
                      int color,
                      int dx,
                      int dy)
{
    int maxRow = board.size() - 1;
    int maxCol = board[0].size() - 1;

    int steps = 0;

    while (true)
    {
        x += dx;
        y += dy;
        steps++;

        if (x < 0 || x > maxRow || y < 0 || y > maxCol)
            break;

        if (board[x][y] != 0)
            return {x, y, steps, 'R'};
    }

    return {-1, -1, steps, 'R'};
}
