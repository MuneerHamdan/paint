#pragma once
struct color{
  unsigned char r, g, b;
};
typedef struct color Color;
struct point{
  unsigned char y;
  unsigned char x;
  Color* color;
};
typedef struct point Point;

Color* makeColor(unsigned char r, unsigned char g, unsigned char b);

Point* makePoint(unsigned char y, unsigned char x, Color* color);
