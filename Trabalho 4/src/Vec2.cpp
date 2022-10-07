#include "../include/Vec2.h"
#include <math.h>

Vec2 :: Vec2(){

}

Vec2 :: Vec2(float x, float y){
	this->x = x;
	this->y = y;
}

Vec2 Vec2 :: operator+ (Vec2 vetor){
	return Vec2(this->x + vetor.x, this->y + vetor.y);
}

Vec2 Vec2 :: operator- (Vec2 vetor){
	return Vec2(this->x - vetor.x, this->y - vetor.y);
}

Vec2 Vec2 :: operator* (float escalar){
	return Vec2(this->x * escalar, this->y * escalar);
} //Mutiplicação de vetor por escalar

float Vec2 :: magnitude(){
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vec2 Vec2 :: normal_vet (float escalar, Vec2 &vetor){
	return Vec2(vetor.x * escalar, vetor.y * escalar);
} //Cálculo do vetor normalizado

float Vec2 :: distPP(Vec2 &vetor){
	return (*this - vetor).magnitude();
} //Distância entre dois pontos

float Vec2 :: incline_x(){
	return atan(this->x);
} //Inclinação de um vetor em relação ao eixo x

float Vec2 :: reta_pontos(Vec2 &vetor){
	return atan2((*this - vetor).y, (*this - vetor).x);
} //Inclinação da reta dad por dois pontos 

Vec2 Vec2 :: rotate(float angulo){
	Vec2 aux;
	float cosx = cos(angulo);
	float senx = sin(angulo);
	aux.x = (this->x * cosx) - (this->y * senx);
	aux.y = (this->y * cosx) + (this->x * senx);
	return aux;
}  //Rotação em um determinado ângulo 

Vec2 Vec2:: operator+=(Vec2 vetor){
	*this = Vec2(this->x+vetor.x,this->y+vetor.y);
}

Vec2 Vec2:: normalized(){
 if(this -> x != 0 && this -> y != 0)
        return Vec2(this->x/this->magnitude(), this->y / this->magnitude());
    return *this;
}