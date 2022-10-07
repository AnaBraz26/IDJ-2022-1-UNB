#include "../include/Camera.h"
#include <stdio.h>
#include <string>

Vec2 Camera :: pos;
Vec2 Camera :: speed;
GameObject *Camera :: focus;

void Camera :: Follow(GameObject* newFocus){
    focus = newFocus;
}

void Camera :: Unfollow(){
    focus = nullptr;
}

void Camera :: Update(float dt){
    speed = Vec2(0,0);
    int vel = 200;
    if(focus != nullptr){
        pos.x = focus->box.center().x;
        pos.y = focus->box.center().y;
    } 
    else{
        if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
            speed = Vec2(0,-1);
        }
        if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
            speed = Vec2(0,1);
        }
        if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
            speed = Vec2(-1,0);
        }
        if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
            speed = Vec2(1,0);
        }
    }

    pos += speed.normalized() * vel * dt;
}