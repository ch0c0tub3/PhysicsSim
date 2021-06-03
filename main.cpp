#include "game/psGameLoader.h"
#include "util/psFileLoader.h"

int main(void) {

	psGameLoader game(1280, 960, "PhysicsSim", 25.f, 60.f);
	if (game.setup())
		return EXIT_FAILURE;

	game.run();
	game.terminate();

	return EXIT_SUCCESS;
}