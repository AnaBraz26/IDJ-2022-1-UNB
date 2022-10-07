#include <string>
#include "GameObject.h"
#include "Component.h"
#include "Vec2.h"
#include <queue>
#include "InputManager.h"
using namespace std;
#ifndef COLLIDER_H
#define COLLIDER_H

class Collider : public Component{
     private:
        //bool debug;
        Vec2 scale;
        Vec2 offset;

    public:
        Collider(GameObject& associated, Vec2 scale = {1, 1}, Vec2 offset = {0, 0});
        Rect box;
        void Update(float dt);
        void Render();
        bool Is(string type);
        void SetScale(Vec2 scale);
        void SetOffset(Vec2 offset);
        void Start();
        bool IsColliding(Collider collidingRect);
        void NotifyCollision(GameObject& other);
};





#endif