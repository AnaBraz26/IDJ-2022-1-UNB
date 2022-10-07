#include "../include/Alien.h"
#include "../include/Game.h"
#include "../include/Collider.h"
#include "../include/Sound.h"
#include <stdio.h>
#include <string>

int Alien::aliencount = 0;
bool Alien::canMove = false;

Alien :: Alien(GameObject &associated, int nMinions, float timeOffset): Component(associated){
    // adiciona a figura do alien
    Sprite *sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);
    hp = 100;
    speed = Vec2(0,0);
    this->nMinions = nMinions;

    //Trabalho 6
    Collider *collider = new Collider(associated);
    associated.AddComponent(collider);
    aliencount += 1;
    state = RST;
    rest = new Timer();
    this->timeOffset = timeOffset;
}

Alien :: ~Alien(){
    for(unsigned int i = 0; i < minionArray.size(); i++){
        if(shared_ptr<GameObject> go = minionArray[i].lock()){
            go->RequestDelete();
        }
    
    }
    aliencount -= 1;
    
}

void Alien :: Start(){
    for(int i = 0; i < nMinions; i++){
        State* instance = &Game::GetInstance().GetCurrentState();
        GameObject *go = new GameObject();
        weak_ptr<GameObject> aliencenter = instance->GetObjectPtr(&associated);
        Minion *minion = new Minion(*go, aliencenter, (M_PI*(1+2*i*360/nMinions))/360);
        go->AddComponent(minion);
        minionArray.push_back(instance -> AddObject(go));
        //Camera::Follow(go);
    }
}

void Alien :: Update(float dt){
    InputManager input = InputManager::GetInstance(); 
    int vel = 256;

    if(hp <= 0){
            associated.RequestDelete();
    }
    else{
        rest->Update(dt);
        Vec2 alien_pos = Vec2(associated.box.x, associated.box.y);
        if(state == RST){
            if(rest->Get() >= 0.5){
                Vec2 destiny_center;
                PenguinsBody *pbody = PenguinsBody::player;
                if(pbody != nullptr){
                    destiny_center.x = pbody->GetPosition().center().x - associated.box.w/2;
                    destiny_center.y = pbody->GetPosition().center().y - associated.box.h/2;
                    destionation = Vec2(destiny_center.x, destiny_center.y);
                    speed = (destiny_center-alien_pos).normalized();
                    state = MV;
                }
            }
        }
    

        associated.angleDeg -= M_PI/180*dt*vel*8;
        
        if(state == MV){
            bool arrived = false;
            alien_pos += speed*dt*vel;
            if(std::abs(alien_pos.distPP(destionation)) <= 325){
                arrived = true;
                speed = Vec2(0,0);
            }
            associated.box.x = alien_pos.x;
            associated.box.y = alien_pos.y;
            if(arrived){
                Vec2 destiny_center;
                PenguinsBody *pbody = PenguinsBody::player;
                if(pbody != nullptr){
                    destiny_center.x = pbody->GetPosition().center().x;
                    destiny_center.y = pbody->GetPosition().center().y;
                    destionation = Vec2(destiny_center.x, destiny_center.y);

                    int minionN = ClosestMinion(destionation);
                    if(minionN != 1){
                        if(shared_ptr<GameObject> go = minionArray[minionN].lock()){
                            Minion *minion = (Minion*)go->GetComponent("Minion");
                            minion->Shoot(destionation);
                        }
                        state = RST;
                        rest->Restart();
                    }
                }
            }
        }   
    } 
}

void Alien :: Render(){

}

bool Alien :: Is(std::string type){
    if(type == "Alien"){
        return true;
    }
    return false;
}

int Alien :: ClosestMinion(Vec2 pos){
    int minion;
    float min_distance = 999999999;
    for(unsigned int i = 0; i < minionArray.size(); i++){
        if(shared_ptr<GameObject> go = minionArray[i].lock()){
            Vec2 aux = Vec2(go->box.x,go->box.y);
            float dist = aux.distPP(pos);
            if(dist <= min_distance){
                min_distance = dist;
                minion = i;
            }
        }
    }
    return minion;
}

void Alien::NotifyCollision(GameObject& other){
    Bullet *bullet = (Bullet*)other.GetComponent("Bullet");

    if(bullet != nullptr){
        if(!bullet->targetsPlayer){
            other.RequestDelete();           
            hp -= bullet->GetDamage();

            if(hp <= 0){
                GameObject *go = new GameObject();
                State *instance = &Game::GetInstance().GetCurrentState();
                go->angleDeg = associated.angleDeg;
                Sprite *sprite = new Sprite(*go, "img/aliendeath.png", 4, 0.1, 0.4);
                go->box.x = associated.box.center().x - go->box.w/2;
                go->box.y = associated.box.center().y - go->box.h/2;
                Sound *sound = new Sound(*go, "audio/boom.wav");
                sound->Play(0);
                go->AddComponent(sound);
                go->AddComponent(sprite);
                instance->AddObject(go);

                for(unsigned int i = 0; i < minionArray.size(); i++){
                    if(shared_ptr<GameObject> go = minionArray[i].lock()){
                        GameObject *go2 = new GameObject();
                        Sprite *minionsprite = (Sprite*) go->GetComponent("Sprite");
                        go2->angleDeg = go->angleDeg;
                        Vec2 scale = minionsprite->GetScale();
                        Sprite *sprite = new Sprite(*go2, "img/aliendeath.png", 4,0.1, 0.4);
                        sprite->SetScale(scale.x*0.5, scale.y*0.5);
                        go2->box.x = go->box.center().x - go2->box.w/2;
                        go2->box.y = go->box.center().y - go2->box.h/2;
                        go2->AddComponent(sprite);
                        instance->AddObject(go2);
                    }
                }

                for(unsigned int i = 0 ; i< minionArray.size();i++){
                    if(shared_ptr<GameObject> go = minionArray[i].lock())
                        go->RequestDelete();
                }
            }
        }
    }

}