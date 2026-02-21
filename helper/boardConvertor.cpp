using namespace std;

#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include "./../include/board.h"

vector<string> split(string str, char ch)
{
    string acc = "";
    vector<string> returnAnsString;

    for (char val : str)
    {
        if (val == ch)
        {
            returnAnsString.push_back(acc);
            acc = "";
        }
        else
        {
            acc += val;
        }
    }

    if (acc.size() > 0)
        returnAnsString.push_back(acc);

    return returnAnsString;
}

bool isNumber(char c)
{
    return c >= '0' && c <= '9';
}

struct resBoard
{
    vector<vector<int>> board;
    Color color;
};

const unordered_map<int, string> indexToCoordinate = {
    {0, "a"},
    {1, "b"},
    {2, "c"},
    {3, "d"},
    {4, "e"},
    {5, "f"},
    {6, "g"},
    {7, "h"},
};

resBoard FENToVector(const string &FEN)
{
    vector<string> parts = split(FEN, ' ');

    if (parts.size() < 2)
        throw runtime_error("Invalid FEN");

    string placement = parts[0];
    string activeColor = parts[1];

    vector<string> ranks = split(placement, '/');
    if (ranks.size() != 8)
        throw runtime_error("Invalid FEN ranks");

    vector<vector<int>> board(8, vector<int>(8, EMPTY));

    for (int i = 0; i < 8; i++)
    {
        int col = 0;

        for (char ch : ranks[i])
        {
            if (isdigit(ch))
            {
                col += ch - '0';
            }
            else
            {
                if (col >= 8)
                    throw runtime_error("Column overflow");

                // TODO: need handle this
                auto itr = piecesToNum.find(ch);

                if (itr == piecesToNum.end())
                {
                    throw runtime_error("Invalid piece");
                }
                board[i][col] = itr->second;

                col++;
            }
        }

        if (col != 8)
            throw runtime_error("Row does not sum to 8");
    }

    Color color = (activeColor == "w") ? WHITE : BLACK;

    return {board, color};
}

vector<string> vectorToAlgebraicNotation(const vector<vector<int>> &vec)
{
    vector<string> algebraicNotationVector;

    for (vector<int> v : vec)
    {

        string algebraicNotation = "";

        string row = to_string(v[0] + 1);

        auto itr = indexToCoordinate.find(v[1]);
        if (itr == indexToCoordinate.end())
        {
            throw runtime_error("The co-ordinates calculated was out of bound or invalid");
        }
        string col = itr->second;

        algebraicNotation = row + col;
        algebraicNotationVector.push_back(algebraicNotation);
    }

    return algebraicNotationVector;
}
