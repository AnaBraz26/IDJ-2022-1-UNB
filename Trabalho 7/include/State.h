#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Sprite.h"
#include "Music.h"
#include "PenguinsBody.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"
#include "Minion.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "TileMap.h"
#include "Collider.h"
#include "GameData.h"
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
    void Input();

public:
   State();
   virtual ~State();
   virtual void LoadAssets() = 0;
   virtual void Update(float dt) = 0;
   virtual void Render() = 0;
   virtual void Start() = 0;
   virtual void Pause() = 0;
   virtual void Resume() = 0;
   virtual weak_ptr<GameObject> AddObject(GameObject* go);
   virtual weak_ptr<GameObject> GetObjectPtr(GameObject* go);   
   bool QuitRequested();
   bool PopRequested();

protected:
    void StartArray();
    virtual void UpdateArray(float dt);
    virtual void RenderArray();
    bool popRequested;
    bool quitRequested;
    bool started;
    vector<shared_ptr<GameObject>> objectArray;
};

#endif 