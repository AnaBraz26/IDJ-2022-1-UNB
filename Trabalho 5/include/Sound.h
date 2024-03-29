#ifndef SOUND_H
#define SOUND_H
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL
#include "SDL_include.h"
#include "Component.h"
#include "GameObject.h"
#include <string>
#include <stdio.h>


class Sound: public Component {
private:
    Mix_Chunk* chunk;
    int channel;
  
public:
    Sound(GameObject &associated);
    Sound(GameObject &associated, std :: string file);
    ~Sound();
    void Play(int times = 1);
    void Stop();
    void Open(std::string file);
    bool IsOpen();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Start();
};

#endif 