//
// Created by aluno on 20/06/2022.
//

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include <string>
#include <stdio.h>

#ifndef STATE_H
#define STATE_H


class State {
private:
    Sprite bg;
    Music music;
    bool quitRequested;
    static Sprite *instance;
public:
   State();
   bool QuitRequested();
   void LoadAssets();
   void Update(float dt);
   void Render();
};

#endif //TRABALHOS_GAME_H