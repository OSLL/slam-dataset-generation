#include "world/World.h"
#include "simulation/Robot.h"
#include "pathfinding/find_trajectory.h"

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

	//Trajectory trajectory = find_trajectory(world, {});

	Vec P1 {0, 0};
	Vec M1 {0, 1};
	Vec P2 {1, 1};
	Vec M2 {1, 0};

	Polynomial<3> f {0, 1, 1, -1};


	HermiteEdge h1 {P1, M1, P2, M2};
	HermiteEdge h2 {{P1, M_PI / 2.0f}, {P2, 0.0f}};

	cout << h1 << endl;
	cout << h2 << endl;
	
	auto show1 = [&h1](double t)
	{
		cout << "h1(" << t << ") = " << h1(t) << endl;
		cout << "h1'(" << t << ") = " << h1.derivative(t) << endl;
	};

	auto show2 = [&h2](double t)
	{
		cout << "h2(" << t << ") = " << h2(t) << endl;
		cout << "h2'(" << t << ") = " << h2.derivative(t) << endl;
	};

	show1(0.0f);

	cout << endl;

	show2(0.0f);

	cout << endl;

	show1(1.0f);

	cout << endl;

	show2(1.0f);

}
