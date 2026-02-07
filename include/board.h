#pragma once

/*
Color mapping:
WHITE =  1
BLACK = -1
*/
enum Color
{
    WHITE = 1,
    BLACK = -1
};

struct radialDirection
{
    int x;
    int y;
    int dx;
    int dy;
};