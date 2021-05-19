#include "game/psGameLoader.h"
#include "util/psFileLoader.h"

int main(void) {

	psGameLoader game(1080, 608, "PhysicsSim", 60.f, 60.f);
	if (game.setup())
		return EXIT_FAILURE;

	game.run();
	game.terminate();

	return EXIT_SUCCESS;
}