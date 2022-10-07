#include "../include/Face.h"
#include "../include/State.h"
#include "../include/InputManager.h"
#include "../include/Camera.h"
#include <stdio.h>
#include <string>


Face :: Face(GameObject& associated): Component(associated){
    this->hitpoints = 30;
}

void Face :: Damage(int damage){
    this->hitpoints = this->hitpoints - damage;
    if(hitpoints <= 0){ 
        Sound* morreu = (Sound*) this->associated.GetComponent("Sound");
        if(morreu != nullptr){             
            morreu->Play(0);
        }        
        associated.RequestDelete(); 
    }
}

void Face :: Update(float dt){
    InputManager instance = InputManager::GetInstance();
    if(instance.MousePress(LEFT_MOUSE_BUTTON)){
        if(associated.box.Is(Vec2(instance.GetMouseX()+Camera::pos.x, instance.GetMouseY()+Camera::pos.y))){
            Damage(std :: rand() % 10 + 10);
        }
    }
}

void Face :: Render(){

}

bool Face :: Is(std ::string type){
    if (type == "Face"){
        return true;
    }
    return false;
}