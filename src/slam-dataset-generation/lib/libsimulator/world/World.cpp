#include "world/World.h"
#include "math/Vec.h"
#include "world/parsing/SvgParser.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostream;
using std::ifstream;
using std::istreambuf_iterator;

World::World() :
	width(-1),
	height(-1),
	world_boundary(nullptr)
{ }

World::~World() {
	for (Obstacle * p : all_obstacles) {
		delete p;
	}
}

const Obstacle * World::get_world_boundary() const {
	return world_boundary;
}

const vector<Obstacle *> & World::get_obstacles() const {
	return interior_obstacles;
}

const vector<Obstacle *> & World::get_all_obstacles() const {
	return all_obstacles;
}

const Obstacle * World::get_obstacle_by_id(string id) const {

	for (Obstacle * p : all_obstacles) {
		if (p->id == id) {
			return p;
		}
	}

	return nullptr;
}

void World::read_from_disk(const char * filename) {

	SvgParser::parse(filename, *this);

	// Check to see if world_boundary ever got populated
	if (world_boundary == nullptr) {
		cout << "world_boundary was never populated" << endl;
		exit(-1);
	}
}

// Generate svg file from current world and write to destination
void World::write_to_disk(const char * destination) const {
	// Not implemented
}

void World::print(ostream & o, int tabs) const {
	// Print correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	if (all_obstacles.size() != 0) {
		o << "World:" << endl;
		for (const Obstacle * path : all_obstacles) {
			path->print(o, tabs + 1);
		}
	} else {
		o << "World is empty" << endl;
	}
}

bool World::is_valid(const Vec & pos) const {
	// Check if point isn't inside world
	if (!world_boundary->is_in(pos)) {
		return false;
	}

	// Check if point is in any of the interior obstacles
	for (Obstacle * path : interior_obstacles) {
		if (path->is_in(pos)) {
			return false;
		}
	}

	// The point passed all tests, so it's valid
	return true;
}

double World::distance(const ObservationPath & op) const {

	double closest_distance = -1;

	for (const Obstacle * p : all_obstacles) {

		double distance_to_path = p->distance(op);

		if (distance_to_path != -1) {
			if (distance_to_path < closest_distance || closest_distance == -1) {
				closest_distance = distance_to_path;
			}
		}
	}

	return closest_distance;
}

ostream & operator<<(ostream & o, const World & world) {
	world.print(o);
	return o;
}
