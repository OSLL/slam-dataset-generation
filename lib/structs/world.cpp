#include "world.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::istreambuf_iterator;

World::World() :
	width(-1),
	height(-1)
{ }

void World::read_from_disk(const char * source) {

	// Read SVG file into a mutable char buffer
	ifstream file (source);
	if (!file.good()) {
		cout << "Problem opening file at " << source << "...\n";
		exit(-1);
	}
}

// Generate svg file from current world and write to destination
void World::write_to_disk(const char * destination) {
	// Not implemented
}
