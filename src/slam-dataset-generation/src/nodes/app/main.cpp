/*
#include "world/world.h"
#include <vector>
#include "misc/misc.h"
#include "simulation/robot.h"

#include "pathfinding/find_critical_poses.h"
#include "pathfinding/find_trajectory.h"
*/


#include <iostream>
#include "math/function.h"
#include "math/cubicpolynomial.h"

using namespace std;

int main(int argc, char ** argv) {
	
	/*
	// Quickly parse command line arguments
	if (argc != 2) {
		cout << "USAGE: test <in.svg>" << endl;
		return -1;
	}

	const char * source = argv[1];

	World world;
	world.read_from_disk(source);

	critical_poses_t critical_poses = find_critical_poses(world);
	Trajectory trajectory = find_trajectory(world, critical_poses);

	//draw_world_and_trajectory(world, trajectory, "map.png");
	
	Robot robot(world, trajectory);
	robot.simulate("data.bag");
	*/

	math::Function<CubicPolynomial> f(1, 2, 3, 4);
	auto zeros = f.zeros();

	for (auto & zero : zeros) {
		cout << "Zero: " << zero << endl;
	}
}
