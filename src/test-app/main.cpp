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

	/* STEP 2: Compute critical points */
	//vector<Vec2D> critical_points = compute_critical_points(world);

	/* STEP 3: Compute trajectory */
	//Path trajectory = compute_trajectory(world, critical_points);

	/* STEP 4: Simulate trajectory, construct bag file, and write to disk */
	//simulate_trajectory(world, trajectory);
}
