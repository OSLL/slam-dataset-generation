#include <iostream>
#include <vector>
#include <cmath>
#include "misc/vec.h"
#include "misc/line.h"
#include "world/world.h"

using namespace std;

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}
	const char * source = argv[1];

	World world;
	world.read_from_disk(source);

	Edge * e = world.get_world_boundary()->edges.back();

	/*
	cout << *e << endl;
	cout << r << endl;
	cout << e->distance(r) << endl;
	*/
	
	Line l({70, 90}, {90, 90});
	cout << e->distance(l) << endl;
}
