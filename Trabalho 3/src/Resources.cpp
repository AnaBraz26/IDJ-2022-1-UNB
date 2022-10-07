#include "../include/Resources.h"
#include "../include/Game.h"
#include <string>
#include <stdio.h>
#include <unordered_map>

unordered_map<std::string, SDL_Texture*> Resources :: imageTable;
unordered_map<std::string, Mix_Music*> Resources :: musicTable;
unordered_map<std::string, Mix_Chunk*> Resources :: soundTable;

SDL_Texture* Resources :: GetImage(std::string file){
	auto it = imageTable.find(file); 
	if(it == imageTable.end()){
		return imageTable[file] = IMG_LoadTexture( Game::GetInstance().GetRenderer(), file.c_str());
	}
	else{
		return it->second;
	}
}

void Resources :: ClearImages(){
	for(auto i = imageTable.begin(); i != imageTable.end(); i++){
		SDL_DestroyTexture(i->second);
	}
}

Mix_Music* Resources :: GetMusic(std::string file){
	auto it = musicTable.find(file); 
	if(it == musicTable.end()){
		return musicTable[file] = Mix_LoadMUS(file.c_str());
	}
	else{
		return it->second;
	}
}

void Resources :: ClearMusics(){
	for(auto i = musicTable.begin(); i != musicTable.end(); i++){
			Mix_FreeMusic(i->second);
		}
}

Mix_Chunk* Resources :: GetSound(std::string file){
	auto it = soundTable.find(file); 
	if(it == soundTable.end()){
		return soundTable[file] =  Mix_LoadWAV(file.c_str());
	}
	else{
		return it->second;
	}
}

void Resources :: ClearSounds(){
	for(auto i = soundTable.begin(); i != soundTable.end(); i++){
		Mix_FreeChunk(i->second);
	}
}