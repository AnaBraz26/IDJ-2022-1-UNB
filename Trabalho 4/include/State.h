#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Face.h"
#include <memory>
#include <math.h>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifndef STATE_H
#define STATE_H


class State {
private:
    Music *music;
    bool quitRequested;
    void Input();
    void AddObject(int mouseX, int mouseY);
    vector <unique_ptr<GameObject>> objectArray;
    
public:
   State();
   ~State();
   bool QuitRequested();
   void LoadAssets();
   void Update(float dt);
   void Render();

};

#endif 