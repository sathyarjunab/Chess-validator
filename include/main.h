#ifndef CHESS_VALIDATOR_H
#define CHESS_VALIDATOR_H

#include <string>
#include <vector>

std::vector<std::string> giveMeMove(
    const std::string &fen,
    const std::string &pieceMove,
    const std::string &kingPosition);

#endif