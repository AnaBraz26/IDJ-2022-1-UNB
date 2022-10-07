
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
#include "Collider.h"
using namespace std;

#ifndef STAGESTATE_H
#define STAGESTATE_H

class StageState : public State {
    private:
    TileSet *tileSet;
    Music *BackgroundMusic;
    public:

    StageState();
    ~StageState();
    void LoadAssets();
    void Update(float dt);
    void Render();
    void Start();
    void Pause();
    void Resume();
};
#endif