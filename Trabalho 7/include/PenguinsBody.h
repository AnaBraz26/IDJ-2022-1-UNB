#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include "SDL_include.h"
#include <string>
#include <stdio.h>
#include <queue>
#ifndef PENGUINSBODY_H
#define PENGUINSBODY_H

class PenguinsBody: public Component{
    private:
       std::weak_ptr<GameObject> pcannon;
       Vec2 speed;
       float linearSpeed;
       float angle;
       int hp;

    public:
       PenguinsBody(GameObject& associated);
       ~PenguinsBody();
       void Update(float dt);
       bool Is(std::string type);
       void Render();
       void Start();
       static PenguinsBody* player;
       void NotifyCollision(GameObject& other);
       Rect GetPosition();

};

#endif