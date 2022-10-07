#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <string>
#include <stdio.h>
#include <unordered_map>
using namespace std;

#ifndef RESOURCES_H
#define RESOURCES_H

class Resources {
private:
        static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
        static unordered_map<string, shared_ptr<TTF_Font>> fontTable;
        static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
        static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;
public:
        static shared_ptr<SDL_Texture>GetImage(string file);
        static void ClearImages();

        static shared_ptr<TTF_Font>GetFont(string file, int);
        static void ClearFonts();

        static shared_ptr<Mix_Music> GetMusic(string file);
        static void ClearMusics();

        static shared_ptr<Mix_Chunk> GetSound(string file);
        static void ClearSounds();
};

#endif 