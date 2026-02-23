{
  "targets": [
    {
      "target_name": "chessvalidator",
      "sources": [
        "binding.cpp",
        "board.cpp",
        "pieces/pawn.cpp",
        "pieces/knight.cpp",
        "pieces/king.cpp",
        "pieces/bishop.cpp",
        "pieces/queen.cpp",
        "pieces/rook.cpp",
        "main.cpp",
        "helper/boardConvertor.cpp",
        "helper/helper.cpp",
        "common-moves/traveling.cpp",
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "/include"
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ]
    }
  ]
}
