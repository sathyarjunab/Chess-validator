using namespace std;

// .h file imports "./../../include/rules/"
#include "./../../include/board.h"
#include "./../../include/common-moves/traveling.h"
#include "./../../include/pieces/king.h"

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

void rayScanHitReturn(vector<vector<int>> &board, vector<radialDirection> &validMoves, vector<vector<int>> &direction, int x, int y, Color color)
{
    // Loop through each diagonal direction and perform ray scanning
    for (const auto &d : direction)
    {
        RayScanReturn hit = rayScan(board, x, y, d[0], d[1]);

        int dx = hit.x;
        int dy = hit.y;

        if ((dx >= 0 && dx < board.size() && dy >= 0 && dy < board[0].size()))
        {
            if (board[dx][dy] > 0 && color == BLACK || board[dx][dy] < 0 && color == WHITE)
            {
                validMoves.push_back({dx, dy, d[0], d[1]});
            }
            else
            {
                validMoves.push_back({hit.prevXIndex, hit.prevYIndex, d[0], d[1]});
            }
        }
        else
        {
            // No piece found in this direction, so we can move there
            validMoves.push_back({hit.prevXIndex, hit.prevYIndex, d[0], d[1]});
        }
    }
}

void rayMovementSquares(vector<vector<int>> &board, vector<vector<int>> &safeMoves, vector<radialDirection> &validMoves, int x, int y, int kingX, int kingY, Color color)
{

    // Loop through each valid move and check if it puts the king in check
    for (const radialDirection &move : validMoves)
    {
        int cX = x;
        int cY = y;
        bool shouldBreak = false;

        while (cX + move.dx >= 0 && cX + move.dx < 8 && cY + move.dy >= 0 && cY + move.dy < 8)
        {

            cX += move.dx;
            cY += move.dy;

            int temp = board[cX][cY];
            board[cX][cY] = board[x][y];
            board[x][y] = EMPTY;

            if (!isKingInCheck(board, kingX, kingY, color))
            {
                safeMoves.push_back({cX, cY});
            }

            board[x][y] = board[cX][cY];
            board[cX][cY] = temp;

            if ((cX == move.x && cY == move.y) || board[cX][cY] != 0)
            {
                break;
            }
        }
    }
}