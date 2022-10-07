#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "../include/SDL_include.h"
#include "../include/Game.h"

int main(int argc, char** argv) {
	Game& game = Game::GetInstance();

	game.Run();

	return 0;
}