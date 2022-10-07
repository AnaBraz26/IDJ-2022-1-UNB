#include "../include/Bullet.h"

Bullet::Bullet(GameObject &associated, float angle, float speed, int damage, float maxDistance, string sprite) : Component(associated){
    Sprite *spr = new Sprite(associated, sprite);
    associated.AddComponent(spr);
    this -> speed = Vec2(1,0);
    this -> speed = this->speed.rotate(angle)*speed;
    distanceLeft = maxDistance;
    this -> damage = damage;
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
    printf("%f\n", distanceLeft);
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
