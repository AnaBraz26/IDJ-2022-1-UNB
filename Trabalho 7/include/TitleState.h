#define INCLUDE_SDL
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h" 
#include "CameraFollower.h"
#include "Alien.h"
#include "TileMap.h"
#include "State.h"
#include "PenguinsBody.h"
#include <memory>
#include <math.h>
#include "Text.h"
#include "Collider.h"
using namespace std;

#ifndef TITLESTATE_H
#define TITLESTATE_H

class TitleState : public State {
    public:

    TitleState();
    ~TitleState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
};
#endif