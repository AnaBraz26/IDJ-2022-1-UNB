#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/Sprite.h"
#include "../include/Game.h"
#include <string>
#include <stdio.h>


Sprite :: Sprite(){
	texture = nullptr;
}

Sprite :: Sprite(std::string file){
	texture = nullptr;
	Open(file);
}

Sprite :: ~Sprite(){
	if(texture){
		SDL_DestroyTexture(texture);		
	}
}

void Sprite :: Open(std::string file){

	//file = "img/ocean.jpg";

	if(texture != nullptr){
		SDL_DestroyTexture(texture);

		texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

		if(texture == nullptr)
		{
			// In the case that the window could not be made...
        	printf("Textura == nullptr: %s\n", SDL_GetError());
		}
		
	}
	else{
		texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

		if(texture == nullptr)
		{
			// In the case that the window could not be made...
        	printf("Textura == nullptr (2): %s\n", SDL_GetError());
		}
	}

	int query_texture = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	if(query_texture){
		// In the case that the window could not be made...
        printf("Textura == nullptr (3): %s\n", SDL_GetError());
	}

	SetClip(0,0,width, height);
}

void Sprite :: SetClip(int x, int y, int w, int h){
	clipRect = SDL_Rect{x,y,w,h};
} 

void Sprite :: Render(int x, int y){
	SDL_Rect dstrect = SDL_Rect{x,y, clipRect.w, clipRect.h};
	int renderCopy = SDL_RenderCopy(Game :: GetInstance().GetRenderer(), texture, &clipRect, &dstrect);
	if(renderCopy){
		// In the case that the window could not be made...
        printf("Não renderizou: %s\n", SDL_GetError());
	}
}

int Sprite :: GetWidth(){
	return width;
}

int Sprite :: GetHeight(){
	return height;
}

bool Sprite :: IsOpen(){
	if(texture != nullptr){
		return true;
	}
	else{
		return false;
	}
}