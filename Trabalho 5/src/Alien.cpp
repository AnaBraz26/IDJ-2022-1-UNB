#include "../include/Alien.h"
#include "../include/Game.h"
#include <stdio.h>
#include <string>

Alien :: Alien(GameObject &associated, int nMinions): Component(associated){
    // adiciona a figura do alien
    Sprite *sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);
    hp = 100;
    speed = Vec2(0,0);
    this->nMinions = nMinions;
}

Alien :: ~Alien(){
    
}

void Alien :: Start(){
    for(int i = 0; i < nMinions; i++){
        State *instance = &Game::GetInstance().GetState();
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
    associated.angleDeg -= M_PI/180*dt*vel*8;
    
    if(input.MousePress(LEFT_MOUSE_BUTTON)){ // verifica o input e caso botão esquedo do mouse atira
        taskQueue.push(Action(SHT, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y));
    }
    else if(input.MousePress(RIGHT_MOUSE_BUTTON)){ //verifica o input e caso botão direito movimenta
        taskQueue.push(Action(MV, input.GetMouseX() + Camera::pos.x, input.GetMouseY() + Camera::pos.y));
    }

    speed = Vec2(0,0);
    
    Vec2 alien_pos = Vec2(associated.box.x, associated.box.y); //pega aposição do alien

    if(taskQueue.size() >= 1){
        Action act = taskQueue.front(); //ve a primeira ação da fila de ações
        if(act.type == MV){
            Vec2 destino;
            destino.x = act.pos.x - associated.box.w/2; // calcula a nova posição em relação a x
            destino.y = act.pos.y - associated.box.h/2; // calcula a nova posição em relação a y

            speed += (destino - alien_pos).normalized(); //calcula a velocidade
            alien_pos += speed * dt * vel; //movimento do alien

            if(std::abs(alien_pos.distPP(destino)) <= 5){ // ve a distancia dos pontos do alien 
                alien_pos = destino; //coloca no destino final
                taskQueue.pop();    // exclui a ação da fila
            }
            
            associated.box.x = alien_pos.x ; //atualiza a posição
            associated.box.y = alien_pos.y ; //atualiza a posição

        }
        if(act.type == SHT){
           int minionshoot = ClosestMinion(act.pos);
           if(shared_ptr<GameObject> go = minionArray[minionshoot].lock()){
                Minion *minion = (Minion*) go->GetComponent("Minion");
                minion->Shoot(act.pos);
                taskQueue.pop();
           }
           
        }
    }

    if(hp <= 0){
            associated.RequestDelete();
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

Alien :: Action :: Action(ActionType type, float x, float y){
    pos.x = x;
    pos.y = y;
    this->type = type;
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