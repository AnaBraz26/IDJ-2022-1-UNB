#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Minion.h"
#include "PenguinsBody.h"
#include "Timer.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#define MV AlienState::MOVING
#define RST AlienState::RESTING
#ifndef ALIEN_H
#define ALIEN_H

class Alien: public Component{
    private:
        enum AlienState{MOVING, RESTING};
        AlienState state;
        Timer *rest;
        Vec2 speed;
        Vec2 destionation;
        int hp;
        int nMinions;
        std::vector<std::weak_ptr<GameObject>> minionArray;
    public:
        static int aliencount;
        Alien(GameObject &associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);        
        int ClosestMinion(Vec2 pos);
        void  NotifyCollision(GameObject& other);
};

#endif