#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include <string>
#include <stdio.h>

#ifndef FACE_H
#define FACE_H

class Face: public Component {
private:
    int hitpoints;
  
public:
    Face(GameObject& associated);
    void Damage(int damage);
    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

#endif