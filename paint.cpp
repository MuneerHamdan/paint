#include "paint.h"
#include <stdlib.h>

Color* makeColor(unsigned char r, unsigned char g, unsigned char b){
  Color* color = (Color*)malloc(sizeof(Color)*1);
  color->r = r;
  color->g = g;
  color->b = b;
  return color;
}

Point* makePoint(unsigned char y, unsigned char x, Color* color){
  Point* point = (Point*)malloc(sizeof(Point)*1);
  point->y = y;
  point->x = x;
  point->color = color;
  return point;
}
