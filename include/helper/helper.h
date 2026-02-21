#pragma once

#include <vector>
#include "./board.h"
#include "./pieces/knight.h"
#include "./common-moves/traveling.h"

using namespace std;

// Checks if the square (x, y) is attacked by any opponent piece
// board      : 8x8 board with integers representing pieces
// x, y       : target coordinates
// kingColor  : color of the king to check against (WHITE or BLACK)
// Returns true if attacked, false otherwise
bool isAttacked(const vector<vector<int>> &board, int x, int y, Color kingColor);