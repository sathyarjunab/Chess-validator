using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <cctype>

#include "./../include/board.h"
#include "./../include/helper/boardConvertor.h"

const unordered_map<int, string> indexToAlgebraicNotation = {
    {0, "h"},
    {1, "g"},
    {2, "f"},
    {3, "e"},
    {4, "d"},
    {5, "c"},
    {6, "b"},
    {7, "a"},
};

const unordered_map<string, int> algebraicNotationToIndex = {
    {"h", 0},
    {"g", 1},
    {"f", 2},
    {"e", 3},
    {"d", 4},
    {"c", 5},
    {"b", 6},
    {"a", 7},
};

resBoard FENToVector(const string &FEN)
{
    vector<string> parts = split(FEN, ' ');

    if (parts.size() < 2)
        throw runtime_error("Invalid FEN");

    string placement = parts[0];
    string activeColor = parts[1];
    string castlingRights = parts[2];
    string enPassant = parts[3];
    string halfMoveClock = parts[4];
    string fullMoveClock = parts[5];

    if (activeColor != "w" && activeColor != "b")
        throw runtime_error("Invalid active color");

    Color color = (activeColor == "w") ? WHITE : BLACK;

    if (halfMoveClock >= "50")
    {
        return {
            {},
            color,
            true,
            {},
            {}};
    }

    vector<string> ranks = split(placement, '/');
    if (ranks.size() != 8)
        throw runtime_error("Invalid FEN ranks");

    vector<vector<int>> board(8, vector<int>(8, EMPTY));

    vector<int> whiteKingPosition;
    vector<int> blackKingPosition;

    for (int i = 0; i < 8; i++)
    {
        int col = 0;

        for (char ch : ranks[i])
        {
            if (isdigit(static_cast<unsigned char>(ch)))
            {
                if (ch < '1' || ch > '8')
                    throw runtime_error("Invalid FEN digit");

                col += ch - '0';
                if (col > 8)
                {
                    throw runtime_error("Column overflow");
                }
            }
            else
            {
                if (col > 8)
                {
                    throw runtime_error("Column overflow");
                }

                auto itr = piecesToNum.find(ch);

                if (itr == piecesToNum.end())
                    throw runtime_error("Invalid piece");

                board[i][col] = itr->second;

                if (ch == 'K')
                    whiteKingPosition = {i, col};

                if (ch == 'k')
                    blackKingPosition = {i, col};

                col++;
            }
        }

        if (col != 8)
            throw runtime_error("Row does not sum to 8");
    }

    // TODO: NEED TO HANDLE OTHER PART OF THE FEN AFTER ACTIVE COLOR

    return {board, color, false, whiteKingPosition, blackKingPosition};
}

vector<string> vectorToAlgebraicNotation(const vector<vector<int>> &vec)
{
    vector<string> algebraicNotationVector;

    for (const vector<int> &v : vec)
    {

        string algebraicNotation = "";

        if (v.size() != 2)
            throw runtime_error("The co-ordinates calculated is invalid");

        if (v[0] < 0 || v[1] < 0 || v[0] > 7 || v[1] > 7)
            throw runtime_error("The co-ordinates calculated was out of bound or invalid");

        string row = to_string(v[0] + 1);

        auto itr = indexToAlgebraicNotation.find(v[1]);
        if (itr == indexToAlgebraicNotation.end())
        {
            throw runtime_error("The co-ordinates calculated was out of bound or invalid");
        }
        string col = itr->second;

        algebraicNotation = col + row;
        algebraicNotationVector.push_back(algebraicNotation);
    }

    return algebraicNotationVector;
}

CoOrdinates algebraicNotationToVector(const string &algebraicNotation)
{
    if (algebraicNotation.size() != 2)
    {
        throw runtime_error("Invalid algebraic notation");
    }

    auto itr1 = algebraicNotationToIndex.find(algebraicNotation.substr(0, 1));
    if (itr1 == algebraicNotationToIndex.end())
        throw runtime_error("Invalid algebraic notation");

    int y = itr1->second;

    if (algebraicNotation[1] < '1' || algebraicNotation[1] > '8')
        throw runtime_error("Invalid algebraic notation");

    int x = algebraicNotation[1] - '1';

    return {x, y};
}

vector<string> split(const string &str, char ch)
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
