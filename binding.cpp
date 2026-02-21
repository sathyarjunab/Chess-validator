#include <napi.h>
#include "./include/main.h"

Napi::Boolean ValidateWrapped(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    if (info.Length() != 2)
        Napi::TypeError::New(env, "Need fen and move").ThrowAsJavaScriptException();

    std::string fen = info[0].As<Napi::String>();
    std::string move = info[1].As<Napi::String>();
    std::string kingPosition = info[2].As<Napi::String>();

    // TODO: Connect this to the actual validation logic when implemented.
    // Expected signature: bool validateMove(std::string fen, std::string move);
    // string move = giveMeMove(fen, move);

    return Napi::Boolean::New(env, true);
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set("validateMove", Napi::Function::New(env, ValidateWrapped));
    return exports;
}

NODE_API_MODULE(chessvalidator, Init)
