#include "../include/Text.h"
#include "../include/Game.h"
#include <stdio.h>

Text::Text(GameObject &associated) :  Component(associated){
    
}
Text::Text(GameObject &associated, string fontFile,int fontSize, TextStyle style, string text, SDL_Color color,float blinkTime) :  Component(associated){
    this ->fontFile = fontFile;
    this -> fontSize = fontSize;
    this -> style = style;
    this -> text = text;
    this -> texture = nullptr;
    this -> color = color;
    this -> blinkTime = blinkTime;
    this -> timer = new Timer();
    font = Resources::GetFont(fontFile, fontSize);
    RemakeTexture();
}

Text::~Text(){
    if(texture != nullptr)
        SDL_DestroyTexture(texture);
    texture = nullptr;
}

void Text::Update(float dt){
    if(blinkTime > 0){
        timer->Update(dt);
        if(timer->Get() >= blinkTime){
            SDL_Color aux = color;
            if(aux.r != 0)
                aux.r = aux.b = aux.g = 0;
            else{
                aux.r = 33;
                aux.g = 134;
                aux.b = 178;
            }

            SetColor(aux);
            timer->Restart();
        }
    }    
}

void Text::Render(){
    if(texture != nullptr){
        SDL_Rect clipRect,dsrect;
        float x = associated.box.x-Camera::pos.x;
        float y = associated.box.y-Camera::pos.y;
        dsrect.x = x;
        dsrect.y = y;
        dsrect.h = associated.box.h;
        dsrect.w = associated.box.w;

        clipRect = dsrect;
        clipRect.x = clipRect.y = 0;
        if(SDL_RenderCopy(Game::GetInstance().GetRenderer(),texture,&clipRect,&dsrect) != 0)
            printf(SDL_GetError());
    }
}

bool Text::Is(string type){
    if(type == "Text")
        return true;
    return false;
}

void Text::Start(){
    
}
void Text::SetText (string text){
    this -> text = text;
    RemakeTexture();
}

void Text::SetColor (SDL_Color color){
    this -> color = color;
    RemakeTexture();
}

void Text::SetStyle (TextStyle style){
    this -> style = style;
    RemakeTexture();
}

void Text::SetFontFile (string fontFile){
    this -> fontFile = fontFile;
    RemakeTexture();
}

void Text::SetFontSize (int fontSize){
    this -> fontSize = fontSize;
    RemakeTexture();
}

void Text::RemakeTexture (){
    if(texture != nullptr){
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
    SDL_Surface* surface = nullptr;

    switch (style)
    {
    case SOLID:
        surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
        break;
    case BLENDED:
        surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
        break;
    case SHADED:
        surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color,SDL_Color{ 0,0,0,0});
        break;
    
    default:
        surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
        break;
    }
    texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
    if(texture == nullptr){
        printf("Nao foi possivel carregar textura de texto");
        exit(-1);
    }
    SDL_FreeSurface(surface);
    int w, h;
	SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
	associated.box.w = w;
	associated.box.h = h;
}

void Text::NotifyCollision(GameObject& other){

}