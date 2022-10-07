#define INCLUDE_SDL
#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACEBAR SDLK_SPACE
#define W_KEY SDLK_w
#define S_KEY SDLK_s
#define A_KEY SDLK_a
#define D_KEY SDLK_d
#include "SDL_include.h"
#include <stdio.h>
#include <string>
#include <unordered_map>
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

class InputManager{
private: 
    bool mouseState[6];
    int mouseUpdate[6];
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    bool quitRequested;
    int updateCounter;
    int mouseX;
    int mouseY;
  
public:
  InputManager();
  ~InputManager();
  void Update();
  bool KeyPress(int key);
  bool KeyRelease(int key);
  bool IsKeyDown(int key);
  bool MousePress(int button);
  bool MouseRealese(int button);
  bool IsMouseDown(int button);
  int GetMouseX();
  int GetMouseY();
  bool Quitresquested();
  static InputManager& GetInstance();
};

#endif 