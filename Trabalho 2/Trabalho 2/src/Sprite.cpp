#include "../include/Sprite.h"
#include "../include/Game.h"
#include <string>
#include <stdio.h>

Sprite :: Sprite(GameObject &associated): Component(associated){
	texture = nullptr;
}

Sprite :: Sprite(GameObject &associated, std::string file): Component(associated){
	texture = nullptr;
	Open(file.c_str());
}

Sprite :: ~Sprite(){
	//if(texture){
		SDL_DestroyTexture(texture);		
	//}
}

void Sprite :: Open(std::string file){

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

		int query_texture = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
		if(query_texture)
		{
			// In the case that the window could not be made...
		    printf("Textura == nullptr (3): %s\n", SDL_GetError());
		}

		SetClip(0,0,width, height);
		associated.box.w = width;
		associated.box.h = height;
	}
}

void Sprite :: SetClip(int x, int y, int w, int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
} 

void Sprite :: Render(){
	SDL_Rect dstrect; 
	dstrect.x = associated.box.x;
	dstrect.y = associated.box.y;
	dstrect.w = associated.box.w;
	dstrect.h = associated.box.h;

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
	return false;
}

void Sprite :: Update(float dt){

}

bool Sprite :: Is(std :: string type){
	if(type == "Sprite"){
		return true;
	}
	return false;
}