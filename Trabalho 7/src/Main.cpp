#include "../include/Game.h"
#include <iostream>
int main(int argc, char** argv) {
	Game::GetInstance().Push(new TitleState());

	Game::GetInstance().Run();
	std::cout << "oi" << std::endl;
	return 0;
}