#include "../include/Rect.h"
#include <math.h>


Rect :: Rect(){

}

Rect :: Rect (float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

Rect Rect :: operator+(Vec2 vetor){
    return Rect(this->x + vetor.x, this->y + vetor.y, this->w, this->h);
}

Rect operator+(Vec2 vetor, Rect rect) {
    return Rect(rect.x + vetor.x, rect.y + vetor.y, rect.w, rect.h);
}//Soma de Rect com Vec2

Vec2 Rect :: center(){
    return Vec2(this->x + this->w/2, this->h/2 + this->y);
}//Distancia entre o centro de dois Reacts

bool Rect :: Is(Vec2 vetor){
    if (((vetor.x > this->x) && (vetor.x < (this->x + this->w))) && 
    ((vetor.y > this->y) && (vetor.y < (this->y + this->h)))){

        return true;
    }

    return false;
}//Saber se ta dentro do Rect