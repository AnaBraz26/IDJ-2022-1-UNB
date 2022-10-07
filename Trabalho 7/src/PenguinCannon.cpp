#include "../include/PenguinCannon.h"
#include "../include/Bullet.h"
#include "../include/Game.h"
#include "../include/Collider.h"
#include <stdio.h>
#include <string>

PenguinCannon :: PenguinCannon(GameObject &associated,weak_ptr<GameObject> penguinBody): Component(associated){
    Sprite *sprite = new Sprite(associated,"img/cubngun.png");
    associated.AddComponent(sprite);
    angle = 0;
    pbody = penguinBody;

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
    timer = nullptr;

}

void PenguinCannon :: Update(float dt){
    InputManager instance = InputManager :: GetInstance();
    if(timer != nullptr){
        timer->Update(dt);
    }
    if(shared_ptr<GameObject> go = pbody.lock()){
        associated.box.x = go->box.center().x - associated.box.w/2;
        associated.box.y = go->box.center().y - associated.box.h/2;
        Vec2 centerPos = Vec2(instance.GetMouseX()+Camera::pos.x, instance.GetMouseY()+Camera::pos.y);
        Vec2 pos = associated.box.center();
        angle = pos.reta_pontos(centerPos);
        associated.angleDeg = angle*180/M_PI;
        if(instance.IsMouseDown(LEFT_MOUSE_BUTTON)){
            Shoot();
        }
    }
    else{
        associated.RequestDelete();
    }
}

bool PenguinCannon :: Is(string type){
    if(type == "PeguinCannon"){
            return true;
        }
        return false;

}

void PenguinCannon :: Shoot(){
    if(timer == nullptr || timer->Get() >= 0.5){
        Sprite *sprite = (Sprite*)associated.GetComponent("Sprite");
        Vec2 pos = associated.box.center();
        Vec2 aux = Vec2(sprite->GetWidth()/2, 0).rotate(angle)+pos;
        GameObject *go = new GameObject();
        go->box.x = aux.x;
        go->box.y = aux.y;
        go->angleDeg = angle*180/M_PI;

        Bullet *bullet = new Bullet(*go, angle, 512,50,1024,"img/penguinbullet.png", 4, false);
        go->AddComponent(bullet);
        State *instance = &Game::GetInstance().GetCurrentState();
        instance -> AddObject(go);

        if(timer == nullptr){
            timer = new Timer();
        }
        
        timer->Restart();
    } 
    
}

void PenguinCannon :: Render(){

}

void PenguinCannon :: Start(){

}

void PenguinCannon::NotifyCollision(GameObject& other){

}