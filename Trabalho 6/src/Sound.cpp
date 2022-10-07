#include "../include/Sound.h"
#include "../include/Resources.h"
#include <stdio.h>
#include <string>


Sound :: Sound(GameObject &associated): Component(associated){
    this->chunk = nullptr;
}

Sound :: Sound(GameObject &associated, std :: string file): Sound(associated){
    Open(file);
}

Sound :: ~Sound(){
    
}

void Sound :: Play(int times){
    this->channel = Mix_PlayChannel(-1, this->chunk, times);
    if(this->channel == -1){
       printf("Nao abriu o mix_playchannel (Sound.cpp): %s\n", SDL_GetError());
    }
}

void Sound :: Stop(){
    if(chunk != nullptr){
        Mix_HaltChannel(this->channel);
    }    
}

void Sound :: Open(std :: string file){
    this->chunk = Resources::GetSound(file);
    if(this->chunk== nullptr){
        // In the case that the window could not be made...
        printf("Nao abriu o sound (Sound.cpp): %s\n", SDL_GetError());
    }
}

bool Sound :: IsOpen(){
    if(Mix_Playing(this->channel)){
        return true;
    }
    return false;
}

void Sound :: Update(float dt){

    
}

void Sound :: Render(){

}

bool Sound:: Is(std ::string type){
    if (type == "Sound"){
        return true;
    }
    return false;
}

void Sound :: Start(){}

void Sound::NotifyCollision(GameObject& other){}