#include <napi.h>
#include <string>
#include <vector>

#include "./include/main.h"

Napi::Value ValidateWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() != 3 ||
        !info[0].IsString() ||
        !info[1].IsString() ||
        !info[2].IsString())
    {
        Napi::TypeError::New(env, "Expected (fen, pieceMove, kingMove)")
            .ThrowAsJavaScriptException();
        return env.Null();
    }

    std::string fen = info[0].As<Napi::String>();
    std::string pieceMove = info[1].As<Napi::String>();
    std::string kingMove = info[2].As<Napi::String>();

    // giveMeMove must return vector<string>
    std::vector<std::string> possibleMoves = giveMeMove(fen, pieceMove, kingMove);

    Napi::Array result = Napi::Array::New(env, possibleMoves.size());

    for (size_t i = 0; i < possibleMoves.size(); ++i)
    {
        result[i] = Napi::String::New(env, possibleMoves[i]);
    }

    return result;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("validateMove", Napi::Function::New(env, ValidateWrapped));
    return exports;
}

NODE_API_MODULE(chessvalidator, Init)