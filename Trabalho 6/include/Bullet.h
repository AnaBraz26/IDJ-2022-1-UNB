#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include <string>
#include <stdio.h>
#ifndef BULLET_H
#define BULLET_H

class Bullet: public Component{
    private:
       Vec2 speed;
       float distanceLeft;
       int damage;

    public:
       Bullet(GameObject&associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, bool targetsPlayer);
       void Update(float dt);
       bool Is(std::string type);
       int GetDamage();
       void Render();
       void Start();
       bool targetsPlayer;
       void NotifyCollision(GameObject& other);
};

#endif