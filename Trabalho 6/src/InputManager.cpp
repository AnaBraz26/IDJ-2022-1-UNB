#include "../include/InputManager.h"
#include <stdio.h>
#include <string>

InputManager& InputManager :: GetInstance(){
    static InputManager instance;
    return instance;
}

InputManager :: InputManager(){
    updateCounter = 0;
    quitRequested = false;
    for(int i = 0; i < 6; i++){
        mouseState[i] = 0;
        mouseUpdate[i] = 0;
        keyState[i] = 0;
        keyUpdate[i] = 0;
    }
    mouseX = 0;
    mouseY = 0;
}

InputManager :: ~InputManager(){

}

void InputManager :: Update(){
    SDL_Event event;
    SDL_GetMouseState(&mouseX, &mouseY);
    quitRequested = false;
    updateCounter++;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT ){
            quitRequested = true;
        }
        if(event.type == SDL_MOUSEBUTTONUP){
            mouseState[event.button.button] = false;
            mouseUpdate[event.button.button] = updateCounter;
        }
        if(event.type == SDL_MOUSEBUTTONDOWN && !event.key.repeat){
            mouseState[event.button.button] = true;
            mouseUpdate[event.button.button] = updateCounter;
        }
        if(event.type == SDL_KEYUP){
            keyState[event.key.keysym.sym] = false;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
        if(event.type == SDL_KEYDOWN && !event.key.repeat){
            keyState[event.key.keysym.sym] = true;
            keyUpdate[event.key.keysym.sym] = updateCounter;
        }
    }
}

bool InputManager :: KeyPress(int key){
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end()){
        if(it->second == updateCounter){
            return keyState.find(key)->second;
        }
        return false;
    }
    return false;
}

bool InputManager :: KeyRelease(int key){
    auto it = keyUpdate.find(key);
    if(it != keyUpdate.end()){
        if(it->second == updateCounter){
            return !keyState.find(key)->second;
        }
        return false;
    }
    return false;
}

bool InputManager :: IsKeyDown(int key){
    auto it = keyState.find(key);
    if(it != keyState.end()){        
        return it->second;
    }
    return false;
}

bool InputManager :: MousePress(int button){
    if(mouseUpdate[button] == updateCounter){
        return mouseState[button];
    }
    return false;
}

bool InputManager :: MouseRealese(int button){
    if(mouseUpdate[button] == updateCounter){
        return !mouseState[button];
    }
    return false;
}

bool InputManager :: IsMouseDown(int button){
    return mouseState[button];
}

int InputManager :: GetMouseX(){
    return mouseX;
}

int InputManager :: GetMouseY(){
    return mouseY;
}

bool InputManager :: Quitresquested(){
    return quitRequested;
}

