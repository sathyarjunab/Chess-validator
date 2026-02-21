#pragma once

#include <vector>
#include <string>

#include "./../board.h"

/*
Assumes Color enum and piece constants (EMPTY, etc.)
are defined in board.h
*/

using std::string;
using std::vector;

struct resBoard
{
    vector<vector<int>> board;
    Color color;
};

vector<string> split(string str, char ch);

bool isNumber(char c);

resBoard FENToVector(const string &FEN);