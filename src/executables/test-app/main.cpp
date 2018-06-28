#include "world/world.h"
#include <vector>
#include "misc/misc.h"
#include "misc/find_roots.h"

#include "pathfinding/find_critical_poses.h"
#include "pathfinding/find_trajectory.h"

#include "simulation/robot.h"

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

	critical_poses_t critical_poses = find_critical_poses(world);
	Trajectory trajectory = find_trajectory(world, critical_poses);

	Robot robot(world, trajectory);
	robot.simulate();
}
