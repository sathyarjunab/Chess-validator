using namespace std;

#include "./../include/common-moves/traveling.h"

#include <stdio.h>
#include <algorithm>
#include <vector>

// vector<vector<int>> bishopMovement(vector<vector<int>> &board, int kingX, int kingY, int x, int y)
// {
//     int direction[4][2] = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};

//     for (const auto &d : direction)
//     {
//         RayScanReturn hit = rayScan(board, kingX, kingY, d[0], d[1]);

//         int dx = hit.x;
//         int dy = hit.y;

//         if (board[dx][dy])
//             ;
//     }
// }