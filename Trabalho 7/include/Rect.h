#include "Vec2.h"

#ifndef RECT_H
#define RECT_H

class Rect {
public:
   float x, y, w, h;
   Rect();
   Rect(float x, float y, float w, float h);
   Rect operator+(Vec2 vetor);
   friend Rect operator+(Vec2 vetor, Rect rect);
   Vec2 center();
   bool Is(Vec2 vetor);

};

#endif 


