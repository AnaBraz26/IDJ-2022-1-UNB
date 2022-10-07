#include "../include/Game.h"
#include <stdio.h>

// Cria a instancia game
Game* Game :: instance = nullptr;
stack<unique_ptr<State>> Game::stateStack;

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

    if(TTF_Init() != 0){
           printf("erro ao abrir texto");
    }

    frametart = 0;
    dt = 0;
    srand(time(NULL));
    storedState = nullptr;
}

Game :: ~Game(){
    if(storedState != nullptr){
        delete(storedState);
    }
    while(!stateStack.empty()){
        stateStack.pop();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();     
    SDL_Quit();
    TTF_Quit();
}

SDL_Renderer *Game::GetRenderer(){
    return renderer;
}

State& Game :: GetCurrentState(){
    return *stateStack.top();
}

void Game :: Push(State *state){
    storedState = state;
}

Game& Game :: GetInstance(){
    if(instance == nullptr){
        instance = new Game("Ana Caroline da Rocha Braz 212008482", 1024, 600);
    }

    return *instance;
}

void Game::Run(){

    if(storedState != nullptr){
        stateStack.emplace(storedState);
        storedState = nullptr;
        stateStack.top()->Start();
    }
    else{
        exit(0);
    }
    while(!stateStack.top()->QuitRequested() && !stateStack.empty()){
        if(stateStack.top()->PopRequested()){
            stateStack.top()->Pause();
            stateStack.pop();
            if(!stateStack.empty()){
                stateStack.top()->Resume();
            }
        }
        if(storedState != nullptr){
            stateStack.top()->Pause();
            stateStack.emplace(storedState);
            stateStack.top()->Start();
            storedState = nullptr;
        }
        CalculateDeltaTime();
        InputManager::GetInstance().Update();
        stateStack.top()->Update(dt);
        stateStack.top()->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
    //looping do jogo
    while(!stateStack.empty()){
        stateStack.pop();
    }
    Resources :: ClearImages();
    Resources :: ClearMusics();
    Resources :: ClearSounds();
}

void Game :: CalculateDeltaTime(){
    int lastframe = frametart;
    frametart = SDL_GetTicks();
    dt = (frametart - lastframe)/ 1000.0;
}

float Game :: GetDeltaTime(){
    return dt;
}
