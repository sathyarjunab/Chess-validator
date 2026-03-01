#ifndef CHESS_VALIDATOR_H
#define CHESS_VALIDATOR_H

#include <string>
#include <vector>

#include "./board.h"

std::vector<std::string> giveMeMove(
    const std::string &fen,
    const std::string &pieceMove,
    const std::string &kingPosition);

#pragma once
#include <vector>
#include <string>

void pieceCaller(
    std::vector<std::vector<int>> &board,
    std::vector<std::string> &validAlgebraicNotation,
    int piece,
    int x,
    int y,
    int kx,
    int ky,
    Color activeColor,
    int enPassantX,
    int enPassantY,
    std::string castlingRights);

#endif