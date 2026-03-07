#include <string>
#include <vector>
#include <cstring>
#include "./include/main.h"

extern "C"
{

    const char *validateMove(const char *fen,
                             const char *pieceMove,
                             const char *kingMove)
    {
        static std::string result;

        std::vector<std::string> moves =
            giveMeMove(fen, pieceMove, kingMove);

        result.clear();

        for (size_t i = 0; i < moves.size(); ++i)
        {
            result += moves[i];
            if (i != moves.size() - 1)
                result += ",";
        }

        return result.c_str();
    }
}