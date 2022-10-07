#include "../include/Face.h"
#include "../include/State.h"
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

}

void Face :: Render(){

}

bool Face :: Is(std ::string type){
    if (type == "Face"){
        return true;
    }
    return false;
}