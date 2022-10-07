
#include <string>
#include "GameObject.h"
#include "InputManager.h"
#include "Vec2.h"
#include "Component.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Bullet.h"
#include <memory>
using namespace std;

#ifndef MINION_H
#define MINION_H

class Minion : public Component{
    private:
        weak_ptr<GameObject> alienCenter;
        float arc;
        
    public:
        Minion(GameObject &associated,  weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
        void Update(float dt);
        void Render();
        bool Is(string type);
        void Shoot(Vec2 target);
        void Start();
};


#endif