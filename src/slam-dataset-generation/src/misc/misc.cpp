#include "misc/misc.h"
#include <random>
#include <vector>
#include <iostream>
#include "matplotlib/matplotlib.h"

using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;;
using std::vector;
using std::cout;
using std::endl;

namespace plot = matplotlibcpp;



/*========================================================================*/
struct GraphSegment {
	vector<double> x;
	vector<double> y;
};

void draw_world(const World & world, const char * filename) {
	
	const double timestep = 0.001;

	vector<GraphSegment> segments;

	for (const EdgePath * p : world.get_all_obstacles()) {
		for (const Edge * e : p->edges) {
			GraphSegment new_segment;

			// Draw the entire edge, from t = 0 to t = 1
			for (double t = 0.0f; t < 1.0f; t += timestep) {
				Vec pos = e->get_pos(t);
				new_segment.x.push_back(pos.x);
				new_segment.y.push_back(pos.y);
			}

			segments.push_back(new_segment);
		}
	}

	for (const GraphSegment & segment : segments) {
		plot::plot(segment.x, segment.y, "k-");
	}

	if (filename != nullptr) {
		plot::save(filename);
	}
}

struct TrajectorySegment : GraphSegment{
	bool valid;
};

void draw_trajectory(const World & world, const Trajectory & trajectory, const char * filename) {

	const double timestep = 0.001;
	const int number_of_datapoints = (trajectory.t_max() - trajectory.t_min()) / timestep;

	vector<TrajectorySegment> segments;

	for (double t = trajectory.t_min(); t < trajectory.t_max(); t+= timestep) {
		Pose pose = trajectory(t);
		//bool is_point_valid = world.is_valid(pose.pos);
		bool is_point_valid = true;

		if (segments.size() == 0 || is_point_valid != segments.back().valid) {
			TrajectorySegment new_segment;
			new_segment.valid = is_point_valid;
			segments.push_back(new_segment);
		}

		segments.back().x.push_back(pose.pos.x);
		segments.back().y.push_back(pose.pos.y);
	}

	for (const TrajectorySegment & segment : segments) {
		plot::plot(segment.x, segment.y, (segment.valid? "k-" : "r-"));
	}
	
	if (filename != nullptr) {
		plot::save(filename);
	}
}

void draw_world_and_trajectory(const World & world, const Trajectory & trajectory, const char * filename) {
	
	draw_world(world, nullptr);
	draw_trajectory(world, trajectory, nullptr);

	plot::save(filename);
}
/*========================================================================*/



/*========================================================================*/
double generate_random_number(const double & min, const double & max) {
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_real_distribution<> distribution(min, max);

	return distribution(gen);
}
/*========================================================================*/



/*========================================================================*/
#ifdef __GNUG__
#include <cstdlib>
#include <memory>
#include <cxxabi.h>
// g++ compiler
std::string demangle(const char * name) {
	int status = -4;

	std::unique_ptr<char, void(*)(void *)> res {
		abi::__cxa_demangle(name, NULL, NULL, &status),
		std::free
	};

	return (status==0) ? res.get() : name;
}
#else
// Not g++ compiler
std::string demangle(const char * name) {
	return name;
}
#endif
/*========================================================================*/
