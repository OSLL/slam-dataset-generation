#include <iostream>
#include <vector>
#include "world.h"

using namespace std;

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}
	const char * source = argv[1];

	/* STEP 1: Generate world */
	// World world = World::generate_world();
	World world;
	world.read_from_disk(source);

	cout << "test" << endl;

	for (Vec2D v : world.world_boundary.vertices) {
		cout << v << endl;
	}
}