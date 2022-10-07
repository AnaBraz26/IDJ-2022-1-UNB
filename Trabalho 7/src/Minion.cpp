#include "../include/Minion.h"
#include "../include/Game.h"
#include "../include/Collider.h"
#include <stdio.h>
#include <string>

Minion :: Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg ): Component(associated){
    // Adiciona o minion
    Sprite *sprite = new Sprite(associated, "img/minion.png");
    associated.AddComponent(sprite);
    double scale = 1.25;
    sprite->SetScale(scale,scale);
    
    this->alienCenter = alienCenter;

    if(shared_ptr<GameObject> go = alienCenter.lock()){
        associated.box.x = go->box.center().x - 200 - associated.box.w/2;
        associated.box.y = go->box.center().y + 0 -  associated.box.h/2;
    }

    arc = arcOffsetDeg;
    associated.angleDeg = arcOffsetDeg;

    //Trabalho 6
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);

}

void Minion :: Update(float dt){
    Vec2 center_pos = alienCenter.lock()->box.center(); //preciso do lock para obter shared_ptr
    Vec2 aux = Vec2(200,0).rotate(arc)+center_pos; //rotação pelo arco atual
    arc += 2*M_PI/360*dt*64;
    associated.box.x = aux.x - associated.box.w/2;
    associated.box.y = aux.y - associated.box.h/2;
    associated.angleDeg = (associated.box.center().reta_pontos(center_pos)*360)/(2*M_PI);
   
}

void Minion :: Render(){

}

void Minion :: Shoot(Vec2 target){
    Sprite *sprite = (Sprite *)associated.GetComponent("Sprite");
    Vec2 pos = associated.box.center(); //Vec2(associated.box.center().x + associated.box.w/2-sprite->GetWidth()/2,associated.box.center().y+associated.box.h/2 -sprite->GetHeight()/2);
    float angle = pos.reta_pontos(target);
    Vec2 aux = Vec2(sprite->GetWidth()/2,0).rotate(angle)+pos;
    
    GameObject *go = new GameObject();
    go->box.x = aux.x;
    go->box.y = aux.y;
    go->angleDeg = angle*180/M_PI;

    Bullet *bullet = new Bullet(*go, angle, 512, 20, 1024, "img/minionbullet2.png", 3, true);
    go->AddComponent(bullet);
    State *instance = &Game::GetInstance().GetState();
    instance -> AddObject(go);
}

bool Minion :: Is(string type){
    if(type == "Minion"){
        return true;
    }
    return false;
}

void Minion :: Start(){
    
}

void Minion::NotifyCollision(GameObject& other){

}

Minion :: ~Minion(){}