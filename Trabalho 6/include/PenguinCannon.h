#include <string>
#include "GameObject.h"
#include "InputManager.h"
#include "Component.h"
#include "Vec2.h"
#include "Sprite.h"
#include <queue>
#include "Collider.h"
#include "Timer.h"
#include "Sound.h"
using namespace std;
#ifndef PENGUINCANNON_H
#define PENGUINCANNON_H

class PenguinCannon : public Component{
    private:
        float angle;
        weak_ptr<GameObject> pbody;
        Timer *timer;

    public:
        PenguinCannon(GameObject &associated,weak_ptr<GameObject> penguinBody);
        void Update(float dt);
        void Render();
        void Start();
        bool Is(string type);
        void Shoot();
        void NotifyCollision(GameObject& other);
    
};





#endif