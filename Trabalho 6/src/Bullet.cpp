#include "../include/Bullet.h"
#include "../include/Collider.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite, int frameCount,bool targetsPlayer) : Component(associated){
    Sprite *new_sprite = new Sprite(associated, sprite, frameCount, 1);
    associated.box.x -= new_sprite->GetWidth()/2;
    associated.box.y -= new_sprite->GetHeight()/2;
    associated.AddComponent(new_sprite);
    this -> speed = Vec2(1,0);
    this -> speed = this->speed.rotate(angle)*speed;
    distanceLeft = maxDistance;
    this -> damage = damage;

    //Trabalho 6
    Collider *collider = new Collider(associated,{1,1},{new_sprite->GetWidth()/2.0,0});
    associated.AddComponent(collider);
    this->targetsPlayer = targetsPlayer;
}

int Bullet::GetDamage(){
    return damage;
}


void Bullet::Update (float dt){
    Vec2 pos = Vec2(associated.box.x,associated.box.y);
    pos += speed*dt;
    associated.box.x = pos.x;
    associated.box.y = pos.y;
    distanceLeft -=  (speed*dt).magnitude();
    if(distanceLeft <= 0)
        associated.RequestDelete();
}

void Bullet::Render(){

}

void Bullet::Start(){

}

bool Bullet::Is(string type){
    if(type == "Bullet")
        return true;
    return false;
}

void Bullet::NotifyCollision(GameObject& other){

}