//
// Created by aluno on 20/06/2022.
//

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include <stdio.h>

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
private:
   SDL_Texture* texture;
   int width;
   int height;
   SDL_Rect clipRect;
   static Sprite *instance;
  
public:
   Sprite();
   Sprite(std :: string file);
   ~Sprite();
   void Open(std :: string file);
   void SetClip(int x, int y, int w, int h);
   void Render(int x, int y);
   int GetWidth();
   int GetHeight();
   bool IsOpen();
};

#endif //TRABALHOS_GAME_H