#include "Game.h"

int main() {
	Game& game = Game::Instance();

	game.Init();
	game.Run();
	game.End();

	return 0;
}