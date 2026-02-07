using namespace std;

// .h file imports "./../../include/rules/"
#include "./../../include/common-moves/traveling.h"

using namespace std;

RayScanReturn rayScan(const vector<vector<int>> &board,
                      int x, int y,
                      int dx, int dy)
{
    int maxRow = board.size();
    int maxCol = board[0].size();

    Direction direction;
    if ((dx == 0) ^ (dy == 0))
        direction = ORTHOGONAL;
    else if (abs(dx) == abs(dy))
        direction = DIAGONAL;
    else
        return {-1, -1, 0, INVALID, x, y};

    int steps = 0;

    while (true)
    {
        int nx = x + dx;
        int ny = y + dy;

        if (nx < 0 || nx >= maxRow || ny < 0 || ny >= maxCol)
            return {-1, -1, steps, direction, x, y};

        x = nx;
        y = ny;
        steps++;

        if (board[x][y] != 0)
            return {x, y, steps, direction, x - dx, y - dy};
    }
}
