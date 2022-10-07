#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/Game.h"
#include "../include/Sprite.h"
#include "../include/State.h"
#include "../include/Music.h"
#include "../include/Resources.h"
#include "../include/InputManager.h"
#include <stdio.h>

// Cria a instancia game
Game* Game :: instance = nullptr;

Game::Game(std::string title, int width, int height){
     
    // verifica se quer criar mais instancias
    if(instance != nullptr){
            printf("Logic Error!\n");
    }
    else {
            instance = this;
    }    

    // Inicia o SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    // Inicia a SDL_Image
    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0)
    {
        SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError());
    }

    //Inicia a SDL_mixer
    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MOD ) == 0){
        SDL_Log("Unable to initialize SDL_Mixer: %s", SDL_GetError());
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
        SDL_Log("Unable to initialize Mix_OpenAudio: %s", SDL_GetError());
    }
    
    // Quantos sons tocam simultaneamente
    Mix_AllocateChannels(32);

    //Inicia a janela
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED , width, height, 0);

    // Check that the window was successfully created
    if (window == nullptr) {
        // In the case that the window could not be made...
        printf("Could not create window (Game.cpp): %s\n", SDL_GetError());
    }

    //renderiza a janela
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    if (renderer == nullptr) {
        // In the case that the window could not be made...
        printf("Não renderizou (Game.cpp): %s\n", SDL_GetError());
    }

    frametart = 0;
    dt = 0;
    srand(time(NULL));
}

Game :: ~Game(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();     
    SDL_Quit();
}


State& Game :: GetState(){
    return *state;
}

SDL_Renderer *Game:: GetRenderer(){
    return renderer;
}

void Game::Run(){

    state = new State();
    state->Start(); //trabalho 5

    //looping do jogo
    while(state->QuitRequested() != true){
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }

   Resources :: ClearImages();
   Resources :: ClearMusics();
   Resources :: ClearSounds();
}

Game& Game :: GetInstance(){
    if(instance == nullptr){
        instance = new Game("Ana Caroline da Rocha Braz 2120008482", 1024, 600);
    }

    return *instance;
}

void Game :: CalculateDeltaTime(){
    int lastframe = frametart;
    frametart = SDL_GetTicks();
    dt = (frametart - lastframe)/ 1000.0;
}

float Game :: GetDeltaTime(){
    return dt;
}
