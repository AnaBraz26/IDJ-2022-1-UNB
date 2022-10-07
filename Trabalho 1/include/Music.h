#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include <string>
#include <stdio.h>


#ifndef MUSIC_H
#define MUSIC_H

class Music {
private:
   Mix_Music* music;
  
public:
  Music();
  ~Music();
  Music(std::string file);
  void Play(int times = -1);
  void Stop(int msToStop = 1500);
  void Open(std::string file);
  bool IsOpen();
};

#endif //TRABALHOS_GAME_H