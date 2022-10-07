#ifndef GAMEDATA_H
#define GAMEDATA_H
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h" 
#include "CameraFollower.h"
#include "State.h"
#include <memory>
#include <math.h>
#include "Text.h"
#include "Collider.h"
using namespace std;


class GameData {
    public:
    static bool playerVictory;

};
#endif