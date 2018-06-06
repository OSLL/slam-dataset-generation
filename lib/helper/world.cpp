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

void World::populate_from_file(const char * location) {

	// Read SVG file into a mutable char buffer
	ifstream file (location);
	if (!file.good()) {
		cout << "Problem opening file at " << location << "...\n";
		exit(-1);
	}
}
