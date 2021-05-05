#include "game/psGameLoader.h"
#include "util/psFileLoader.h"

int main(void) {

	if (glewInit())
		return EXIT_FAILURE;

	psGameLoader game(640, 480, "PhysicsSim", 60.f, 20.f);
	if (game.setup())
		return EXIT_FAILURE;

	game.run();
	game.terminate();

	return EXIT_SUCCESS;
}