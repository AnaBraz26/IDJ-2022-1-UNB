#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include "State.h"
#include "StageState.h"
#include "TitleState.h"
#include <string>
#include <stdio.h>
#include <stack>

#ifndef GAME_H
#define GAME_H

class Game {
private:
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *storedState;
    static stack<unique_ptr<State>> stateStack;
    int frametart;
    float dt;
    void CalculateDeltaTime();

public:
    Game(string title, int width, int height);
    ~Game();
    SDL_Renderer* GetRenderer();
    State& GetCurrentState();
    void Push(State *state);
    static Game& GetInstance();    
    void Run();
    float GetDeltaTime();
};

#endif 


