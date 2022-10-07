#include <math.h>

#ifndef VEC2_H
#define VEC2_H

class Vec2{
public:
   float x, y;
   Vec2();
   Vec2(float x, float y);
   Vec2 operator+ (Vec2 vetor);
   Vec2 operator+=(Vec2 vetor);
   Vec2 operator- (Vec2 vetor);
   Vec2 operator* (float escalar);               //Mutiplicação de vetor por escalar
   float magnitude();
   Vec2 normalized();
   Vec2 normal_vet (float escalar, Vec2 &vetor); //Cálculo do vetor normalizado
   float distPP(Vec2 &vetor);                    //Distância entre dois pontos
   float incline_x();                            //Inclinação de um vetor em relação ao eixo x
   float reta_pontos(Vec2 &vetor);               //Inclinação da reta dad por dois pontos 
   Vec2 rotate(float angulo);                    //Rotação em um determinado ângulo 
   friend Vec2 operator*(Vec2 const &vetor,float escalar); //Trabalho 6
   friend Vec2 operator* (float escalar, Vec2 &vetor); //Trabalho 6
};

#endif 