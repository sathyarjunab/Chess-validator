#pragma once

#include <vector>
#include "./../pieces/knight.h"
#include "./../common-moves/traveling.h"

using namespace std;

struct AttackerDetails
{
    int x;
    int y;
    vector<int> direction;
};

struct AttackerReturn
{
    bool isInAttack;
    int numberOfAttacks;
    vector<AttackerDetails> attackers;
};

// Checks if the square (x, y) is attacked by any opponent piece
// board      : 8x8 board with integers representing pieces
// x, y       : target coordinates
// kingColor  : color of the king to check against (WHITE or BLACK)
// Returns true if attacked, false otherwise
AttackerReturn isAttacked(vector<vector<int>> &board, int x, int y, Color pieceColor, bool wantToCheckKingAttack);

vector<AttackerDetails> legallyAttacked(vector<vector<int>> &board,
                                        int x,
                                        int y,
                                        Color pieceColor,
                                        int opponentsKingX,
                                        int opponentsKingY,
                                        vector<AttackerDetails> &attackersList);