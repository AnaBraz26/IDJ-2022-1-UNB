#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/Music.h"
#include "../include/Resources.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include <stdio.h>
#include <string>

Music :: Music(){
	
}

Music :: Music(std::string file){
	Open(file);
}

void Music :: Play(int times){
	if(music != nullptr){	

			Mix_PlayMusic(music, times);
	}
	else{
		printf("Sem música\n");
	}
}

void Music :: Stop(int msToStop){
	Mix_FadeOutMusic(msToStop);
}

void Music :: Open(std::string file){
	music = Resources :: GetMusic(file);
	if(music == nullptr){
		// In the case that the window could not be made...
        printf("Nao abriu a musica (Music.cpp): %s\n", SDL_GetError());
	}
}

bool Music :: IsOpen(){
	if(music != nullptr){
		return true;
	}
	else{
		return false;
	}
}

Music :: ~Music(){
	Stop();
	Mix_FreeMusic(music);
}
