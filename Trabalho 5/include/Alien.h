#include "GameObject.h"
#include "Vec2.h"
#include "Component.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Minion.h"
#include <string>
#include <stdio.h>
#include <vector>
#include <queue>
#define MV Action::ActionType::MOVE
#define SHT Action::ActionType::SHOOT
#ifndef ALIEN_H
#define ALIEN_H

class Alien: public Component{
    private:
        class Action{
            public:
                enum ActionType {MOVE, SHOOT};
                Action(ActionType type, float x, float y);
                ActionType type;
                Vec2 pos;
        };

        Vec2 speed;
        int hp;
        int nMinions;
        std::queue<Action> taskQueue;
        std::vector<std::weak_ptr<GameObject>> minionArray;
    public:
        Alien(GameObject &associated, int nMinions);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);        
        int ClosestMinion(Vec2 pos);
};

#endif