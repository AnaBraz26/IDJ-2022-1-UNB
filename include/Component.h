#ifndef COMPONENT_H
#define COMPONENT_H
#include "GameObject.h"
#include <stdio.h>
#include <string>

class GameObject;

class Component{
protected: 
  GameObject& associated;    
  
public:
  Component(GameObject &associated);
  virtual ~Component();
  void virtual Update(float dt) = 0;
  void virtual Render() = 0;
  bool virtual Is(std :: string type) = 0;
};

#endif 