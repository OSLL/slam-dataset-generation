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
using std::unique_ptr;

World::World()
{ }

void World::addObstacle(unique_ptr<Obstacle> obstacle) {
	
	if (obstacle->getId() == "world_boundary")
	{
		obstacles.insert(obstacles.begin(), std::move(obstacle));
	}
	else
	{
		obstacles.push_back(std::move(obstacle));
	}
}

unique_ptr<Obstacle> World::extractLinearTrajectory() {

	unique_ptr<Obstacle> linear_trajectory = nullptr;

	for (auto itr = obstacles.begin(); itr != obstacles.end(); itr++) {

		if ((*itr)->getId() == "linear_trajectory") {
			linear_trajectory = std::move(*itr);
			obstacles.erase(itr);
			break;
		}
	}

	if (!linear_trajectory) {
		cout << "Could not locate path with id=\"linear_trajectory\"" << endl;
		exit(-1);
	}

	return linear_trajectory;
}

void World::read_from_disk(const char * filename) {

	SvgParser::parse(filename, *this);

	if (obstacles.size() <= 0)
	{
		cout << "No obstacles detected" << endl;
		exit(-1);
	}

	if (obstacles[0]->getId() != "world_boundary")
	{
		cout << "World_boundary not populated" << endl;
		exit(-1);
	}
}

bool World::is_valid(const Vec & pos) const {

	for (auto itr = obstacles.begin(); itr != obstacles.end(); itr++)
	{
		bool is_in = (*itr)->is_in(pos);

		if (itr == obstacles.begin()) // itr points to the world boundary
		{
			if (!is_in)
				return false;
		}
		else
		{
			if (is_in)
				return false;
		}
	}

	// The point passed all tests, so it's valid
	return true;
}

double World::distance(const ObservationPath & op) const {

	double closest_distance = -1;

	for (const auto & obstacle : obstacles) {

		double distance_to_path = obstacle->distance(op);

		if (distance_to_path != -1) {
			if (distance_to_path < closest_distance || closest_distance == -1) {
				closest_distance = distance_to_path;
			}
		}
	}

	return closest_distance;
}

void World::print(ostream & o, int tabs) const {
	// Print correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	if (obstacles.size() != 0) {
		o << "World:" << endl;
		for (const auto & obstacle : obstacles) {
			obstacle->print(o, tabs + 1);
		}
	} else {
		o << "World is empty" << endl;
	}
}

ostream & operator<<(ostream & o, const World & world) {
	world.print(o);
	return o;
}
