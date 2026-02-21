#ifndef BOARD_CONVERTOR_H
#define BOARD_CONVERTOR_H

#include <string>
#include <vector>
#include <unordered_map>

#include "./../board.h"

// --------------------
// Utility Functions
// --------------------

std::vector<std::string> split(const std::string &str, char ch);

// --------------------
// FEN Conversion
// --------------------

struct resBoard
{
    vector<vector<int>> board;
    Color color;
    bool draw;
};

resBoard FENToVector(const std::string &FEN);

// --------------------
// Algebraic Conversion
// --------------------

std::vector<std::string>
vectorToAlgebraicNotation(const std::vector<std::vector<int>> &vec);

struct CoOrdinates
{
    int x;
    int y;
};

CoOrdinates algebraicNotationToVector(const std::string algebraicNotation);

// --------------------
// Lookup Tables
// --------------------

extern const std::unordered_map<int, std::string> indexToAlgebraicNotation;
extern const std::unordered_map<std::string, int> algebraicNotationToIndex;

#endif