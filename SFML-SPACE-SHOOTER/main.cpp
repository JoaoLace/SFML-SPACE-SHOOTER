#include "game.h"
#include <time.h>
int main() {
	srand(time(0));
	
	game game;

	game.run();

	return 0;
}