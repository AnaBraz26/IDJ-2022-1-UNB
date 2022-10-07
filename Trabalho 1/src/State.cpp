#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/State.h"
#include "../include/Game.h"
#include "../include/Sprite.h"

State :: State(): bg("img/ocean.jpg"), music("audio/stageState.ogg"){
	quitRequested = false;
	music.Play();
}

void State :: LoadAssets(){}

void State :: Update(float dt){
	if(SDL_QuitRequested() == true){
		music.Stop();
		quitRequested = true;
	}
}

void State :: Render(){
	bg.Render(0,0);
}

bool State :: QuitRequested(){
	return quitRequested;
}
