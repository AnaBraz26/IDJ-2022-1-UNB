#include "../include/Resources.h"
#include "../include/Game.h"

unordered_map<string,shared_ptr<SDL_Texture >> Resources::imageTable;
unordered_map<string,shared_ptr<TTF_Font >> Resources::fontTable;
unordered_map<string,shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string,shared_ptr<Mix_Music>> Resources::musicTable;

shared_ptr<SDL_Texture>Resources::GetImage(string file){
    auto it = imageTable.find(file);
    SDL_Texture* texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if(it == imageTable.end())
        if(texture != nullptr){
            imageTable[file] = shared_ptr<SDL_Texture>(texture,[](SDL_Texture* ptr){SDL_DestroyTexture(ptr);});
            return imageTable[file];
        }
        else
            return nullptr;
    else
        return it -> second;
}
void Resources::ClearImages(){

    for(auto i = imageTable.begin();i != imageTable.end();i++)
        if(i->second.unique()){
            imageTable.erase(i);
        }
}

shared_ptr<TTF_Font>Resources::GetFont(string file,int size){
    auto it = fontTable.find(file+to_string(size));
    TTF_Font* font = TTF_OpenFont(file.c_str(), size);
    if(it == fontTable.end())
        if(font != nullptr){
            fontTable[file+to_string(size)] = shared_ptr<TTF_Font>(font,[](TTF_Font* ptr){TTF_CloseFont(ptr);});
            return fontTable[file+to_string(size)];
        }
        else
            return nullptr;
    else
        return it -> second;
}
void Resources::ClearFonts(){

    for(auto i = fontTable.begin();i != fontTable.end();i++)
        if(i->second.unique()){
            fontTable.erase(i);
        }
}

shared_ptr<Mix_Music> Resources::GetMusic(string file){
    auto it = musicTable.find(file);
    Mix_Music *music = Mix_LoadMUS(file.c_str());
    if(it == musicTable.end())
        if(music != nullptr){
            musicTable[file] = shared_ptr<Mix_Music>(music,[](Mix_Music* ptr){Mix_FreeMusic(ptr);});
            return musicTable[file];
        }
        else
            return nullptr;
    else
        return it -> second;
}
void Resources::ClearMusics(){
    for(auto i = musicTable.begin();i != musicTable.end();i++)
        if(i->second.unique()){
            musicTable.erase(i);
        }
}

shared_ptr<Mix_Chunk> Resources::GetSound(string file){
    auto it = soundTable.find(file);
    Mix_Chunk *sound = Mix_LoadWAV(file.c_str());
    if(it == soundTable.end())
        if(sound !=  nullptr){
            soundTable[file] = shared_ptr<Mix_Chunk>(sound,[](Mix_Chunk* ptr){Mix_FreeChunk(ptr);});;
            return soundTable[file];
        }
        else
            return nullptr;
    else
        return it -> second;
      
}
void Resources::ClearSounds(){
    for(auto i = soundTable.begin();i != soundTable.end();i++)
        if(i->second.unique()){
            soundTable.erase(i);
        }
}

