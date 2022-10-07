//
// Created by aluno on 20/06/2022.
//
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "State.h"
#include "Sprite.h"
#include <string>
#include <stdio.h>

#ifndef GAME_H
#define GAME_H

class Game {
private:
    Game(std :: string title, int width, int height);
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
public:
    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    bool QuitRequested();
};

#endif //TRABALHOS_GAME_H


