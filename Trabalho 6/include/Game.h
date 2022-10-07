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
    int frametart;
    float dt;
    void CalculateDeltaTime();

public:
    Game(Game& game) = delete;
    void operator=(Game& game) = delete;

    ~Game();
    void Run();
    SDL_Renderer* GetRenderer();
    State& GetState();
    static Game& GetInstance();
    bool QuitRequested();
    float GetDeltaTime();
};

#endif 


