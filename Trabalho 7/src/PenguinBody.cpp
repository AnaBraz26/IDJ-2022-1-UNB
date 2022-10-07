#include "../include/PenguinsBody.h"
#include "../include/PenguinCannon.h"
#include "../include/Game.h"
#include "../include/Collider.h"
#include "../include/Sound.h"
#include <stdio.h>
#include <string>

PenguinsBody* PenguinsBody :: player = nullptr;

PenguinsBody :: PenguinsBody(GameObject& associated): Component(associated){
    Sprite *sprite = new Sprite(associated, "img/penguin.png");
    associated.AddComponent(sprite);
    player = this;
    speed = Vec2(0,0);
    linearSpeed = 0.1;
    angle = 0;
    hp = 10*100;

    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
}

PenguinsBody :: ~PenguinsBody(){
    player = nullptr;
}

Rect PenguinsBody :: GetPosition(){
    return associated.box;
}

void PenguinsBody :: Update(float dt){
    Vec2 penguin_pos = Vec2(associated.box.x, associated.box.y);
    InputManager instance = InputManager::GetInstance();
    if(instance.IsKeyDown(W_KEY)){ //Aperta W
        if(speed.x <= 50){
            speed += Vec2(1,0);
        }
        else{
            speed.x = 40;
        }
    }
    else if(instance.IsKeyDown(S_KEY)){ //Aperta S
        if(speed.x > 0){
            speed += Vec2(-1,0);
        }
        else if(speed.x < 0){
            speed.x = 0;
        }
    }
    else{
        if(speed.x > 0){
            speed = speed - Vec2(linearSpeed, 0);
        }
    }

    //Aperta D
    if(instance.IsKeyDown(D_KEY)){
        angle += M_PI/15*dt*512;
        associated.angleDeg = angle;
    }

    //Aperta A
    if(instance.IsKeyDown(A_KEY)){
        angle -= M_PI/15*dt*512;
        associated.angleDeg = angle;
    }

    penguin_pos += speed.normalized().rotate(angle/180*M_PI)*dt*8;
    
    if (penguin_pos.x >= 1350 || penguin_pos.x <= 0){
        penguin_pos.x = associated.box.x;
    }

    if (penguin_pos.y >= 1280 || penguin_pos.y <= 0){
        penguin_pos.y = associated.box.y;
    }        

    associated.box.x = penguin_pos.x;
    associated.box.y = penguin_pos.y;

    if(hp <= 0){
        if(shared_ptr<GameObject> go = pcannon.lock()){
            go->RequestDelete();
        }
        associated.RequestDelete();
        Camera::Unfollow();
    }
}

void PenguinsBody :: Render(){

}

void PenguinsBody :: Start(){
    State *instance = &Game::GetInstance().GetCurrentState();
    GameObject *go = new GameObject();
    weak_ptr<GameObject> penguinCenter = instance->GetObjectPtr(&associated);
    PenguinCannon *penguinCannon = new PenguinCannon(*go, penguinCenter);
    go->AddComponent(penguinCannon);
    pcannon = instance->AddObject(go);
}

bool PenguinsBody ::  Is(std::string type){
    if(type == "PeguinsBody"){
            return true;
        }
        return false;
}

void PenguinsBody::NotifyCollision(GameObject& other){
    Bullet *bullet = (Bullet*)other.GetComponent("Bullet");
    if(bullet != nullptr){
        if(bullet->targetsPlayer){
            hp -= bullet->GetDamage();
            other.RequestDelete();
           
            if(hp <= 0){
                GameObject *go = new GameObject();
                State *instance = &Game::GetInstance().GetCurrentState();
                Sprite *sprite = new Sprite(*go, "img/penguindeath.png", 5,0.1, 0.5);
                go->box.x = associated.box.center().x - go->box.w/2;
                go->box.y = associated.box.center().y - go->box.h/2;
                Sound *sound = new Sound(*go, "audio/boom.wav");
                sound->Play(0);
                go->AddComponent(sound);
                go->AddComponent(sprite);
                instance->AddObject(go);
            }
        }
    }

}