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
#include "SDL_include.h"
using namespace std;

#ifndef ENDSTATE_H
#define ENDSTATE_H

class EndState : public State {
    public:
        EndState();
        ~EndState();
        void LoadAssets();
        void Update(float dt);
        void Render();
        void Start();
        void Pause();
        void Resume();

    private:
        Music *backgroundMusic;
};
#endif