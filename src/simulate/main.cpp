#include <iostream>
#include <vector>
#include "world.h"
#include "vec2d.h"
#include "path.h"

using namespace std;

vector<Vec2D> compute_critical_points(const World &);
Path compute_trajectory(const World &, const vector<Vec2D> &);
void simulate_trajectory(const World &, const Path &);

int main(int argc, char ** argv) {
	
	// Quickly parse command line arguments
	if (argc != 3) {
		cout << "USAGE: simulate <map.svg> <out.bag>" << endl;
		return -1;
	}
	const char * world_location = argv[1];
	const char * output_location = argv[2];

	/* STEP 1: Recover world from disk */
	World world;
	world.populate_from_file(world_location);

	/* STEP 2: Compute critical points */
	//vector<Vec2D> critical_points = compute_critical_points(world);

	/* STEP 3: Compute trajectory */
	//Path trajectory = compute_trajectory(world, critical_points);

	/* STEP 4: Simulate trajectory, construct bag file, and write to disk */
	//simulate_trajectory(world, trajectory);
}
