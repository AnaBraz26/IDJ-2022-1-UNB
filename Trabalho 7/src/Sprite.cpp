#include "../include/Sprite.h"
#include "../include/Game.h"
#include "../include/Resources.h"
#include "../include/Camera.h"

#include <string>
#include <stdio.h>

Sprite :: Sprite(GameObject &associated): Component(associated){
	texture = nullptr;
	scale.x = 1;
	scale.y = 1;
}

Sprite :: Sprite(GameObject &associated, std::string file, int frameCount , float frameTime, float secondsToSelfDestruct): Component(associated){
	texture = nullptr;
	scale.x = 1;
	scale.y = 1;
	Open(file);
	SetframeCount(frameCount);
	SetFrameTime(frameTime);
	this->secondsToSelfDestruct = secondsToSelfDestruct;
	if(secondsToSelfDestruct > 0){
		selfDestructCount = new Timer();
	}
	else{
		selfDestructCount = nullptr;
	}

}

Sprite :: ~Sprite(){

}

void Sprite :: Open(std::string file){

	if(texture != nullptr){
		SDL_DestroyTexture(texture);

		texture = Resources :: GetImage(file).get();

		if(texture == nullptr)
		{
			// In the case that the window could not be made...
        	printf("Textura == nullptr: %s\n", SDL_GetError());
		}
	}
	else{
		texture = Resources :: GetImage(file).get();

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
	}
	
	SetClip(0,0,width, height);
	associated.box.w = width;
	associated.box.h = height;
}

void Sprite :: SetClip(int x, int y, int w, int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
} 

// Sobrecarga para o RenderTile
void Sprite :: Render(){
	Render(associated.box.x-Camera::pos.x, associated.box.y-Camera::pos.y);// clipRect.w, clipRect.h);
}

void Sprite :: Render(float x, float y){//}, float w, float h){
	SDL_Rect dstrect; 
	dstrect.x = x+clipRect.w/2- clipRect.w/2 *scale.x;
    dstrect.y = y+clipRect.h/2 - clipRect.h/2 *scale.y;
	dstrect.w = clipRect.w * scale.x;
	dstrect.h = clipRect.h * scale.y;
	
	int renderCopy = SDL_RenderCopyEx(Game :: GetInstance().GetRenderer(), texture, &clipRect,&dstrect,associated.angleDeg,nullptr,SDL_FLIP_NONE);
	if(renderCopy != 0){
		// In the case that the window could not be made...
		printf("Não renderizou: %s\n", SDL_GetError());
	}
}

int Sprite :: GetWidth(){
	return (width/frameCount)*scale.x;
}

int Sprite :: GetHeight(){
	return height*scale.y;
}

bool Sprite :: IsOpen(){
	if(texture != nullptr){
		return true;
	}
	return false;
}

void Sprite :: Update(float dt){
	timeElapsed += dt;
	if(selfDestructCount != nullptr){
		selfDestructCount ->Update(dt);
		if(selfDestructCount -> Get()>= secondsToSelfDestruct){
			associated.RequestDelete();
		}
	}
	if(timeElapsed >= frameTime){
		if(currentFrame+1 == frameCount){
			SetFrame(0);
		}
		else{
			SetFrame(currentFrame+1);
		}
	}
}

bool Sprite :: Is(std :: string type){
	if(type == "Sprite"){
		return true;
	}
	return false;
}

void Sprite :: Start(){

}

void Sprite :: SetScale(float scaleX, float scaleY){	
    scale.x = scaleX == 0 ? scale.x : scaleX;
    scale.y = scaleY == 0 ? scale.y : scaleY;
}

Vec2 Sprite :: GetScale(){
	return scale;
}

//Trabalho 6

void Sprite :: SetFrame(int frame){
	currentFrame = frame;
	timeElapsed = 0;
	SetClip(GetWidth()*currentFrame/scale.x, 0, width/frameCount, height);
}

void Sprite :: SetframeCount(int frameCount){
	this->frameCount = frameCount;
	SetFrame(0);
	associated.box.w = GetWidth();
}

void Sprite :: SetFrameTime(float frameTime){
	this->frameTime = frameTime;
	timeElapsed = 0;
}

void Sprite::NotifyCollision(GameObject& other){

}