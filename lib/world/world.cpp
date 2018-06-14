#include "world/world.h"
#include "world/path.h"
#include "world/parsingcontext.h"
#include "misc/vec.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::istreambuf_iterator;

World::World() :
	width(-1),
	height(-1)
{ }

World::~World() {
	for (Path * p : all_obstacles) {
		delete p;
	}
}

const Path * World::get_world_boundary() {
	return world_boundary;
}
const vector<Path *> & World::get_obstacles() {
	return interior_obstacles;
}
const vector<Path *> & World::get_all_obstacles() {
	return all_obstacles;
}

void World::read_from_disk(const char * source) {
	// Check if file can be read
	ifstream file (source);
	if (!file.good()) {
		cout << "Problem opening file at " << source << "...\n";
		exit(-1);
	}

	// Dump file into char buffer
	string file_contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	char * buffer = (char *)file_contents.c_str();

	// Parse document
	ParsingContext parsing_context(*this);
	parsing_context.parse(buffer);
}

// Generate svg file from current world and write to destination
void World::write_to_disk(const char * destination) {
	// Not implemented
}
