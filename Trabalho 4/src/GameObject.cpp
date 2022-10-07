#include "../include/GameObject.h"
#include <stdio.h>
#include <string>

GameObject :: GameObject(){
   isDead = false;
}

GameObject :: ~GameObject(){
    for(unsigned int i = this->components.size() - 1; i >= 0; i--){
        components.erase(this->components.begin() + i);
    }
}

void GameObject :: Update(float dt){
    for(unsigned int i = 0; i < this->components.size(); i++){
        components[i]->Update(dt);
    }
}

void GameObject :: Render(){
    for(unsigned int i = 0; i < this->components.size(); i++){
        components[i]->Render();
    }
}

bool GameObject :: IsDead(){
    return this->isDead;
}

void GameObject :: RequestDelete(){
    this->isDead = true;
}

void GameObject :: AddComponent(Component* cpt){
    this->components.emplace_back(cpt);
}

void GameObject :: RemoveComponent(Component* cpt){
    for(unsigned int i = 0; i < this->components.size(); i++){
        if(this->components[i].get() == cpt)
        {
            components.erase(this->components.begin() + i);
            break;
        } 
    }
}

Component* GameObject :: GetComponent(std :: string type){
    for(unsigned int i = 0; i < this->components.size(); i++){
        if(this->components[i]->Is(type)){
            return components[i].get();
        }
    }
    return nullptr;
}
