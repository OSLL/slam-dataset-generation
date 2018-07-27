#include "world/parsing/SvgParser.h"
#include "world/World.h"
#include "world/parsing/LengthFactory.h"
#include "world/parsing/SvgTransformHandler.h"
#include "math/Pose.h"

#include <string>
#include <iostream>
#include <cstdio>


// Obstacle edge types
#include "obstacle/ObstacleEdge.h"
#include "obstacle/LinearEdge.h"
#include "obstacle/CubicBezierEdge.h"


using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::make_pair;

using namespace svgpp;

SvgParser::SvgParser(World & world_ref)
	: world(world_ref)
	, length_factory_(new LengthFactory())
	, transform_handler_(new SvgTransformHandler())
{ }

SvgParser::~SvgParser()
{ }

/* ======================================== Document information ======================================== */
void SvgParser::set_viewport(double x, double y, double width, double height) {
	viewport_width = width;
	viewport_height = height;

	// Inform transform handler of viewport height
	transform_handler_->setViewportHeight(viewport_height);
}

void SvgParser::set_viewbox_size(double width, double height) {
	viewbox_width = width;
	viewbox_height = height;
}

const LengthFactory & SvgParser::length_factory() {
	return *length_factory_;
}
/* ====================================================================================================== */



/* ========================================= Transform Handling ========================================= */
void SvgParser::transform_matrix(const SvgTransformHandler::Transform & t) {
	transform_handler_->receiveTransform(t);
}

void SvgParser::on_enter_element(const tag::element::any &) {
	transform_handler_->enterElement();
}

void SvgParser::on_exit_element() {
	transform_handler_->exitElement();
}
/* ====================================================================================================== */



/* =========================================== Path detection =========================================== */
void SvgParser::set(const tag::attribute::id &, const boost::iterator_range<const char *> & value) {
	id_.assign(boost::begin(value), boost::end(value));



	// If the id ends in "_trajectory", then it's a trajectory
	//
	// In order for that to happen, id_.length() has to be 12 or greater (the substring is only 11 characters
	// but it must be prefaced by a unique identifier, e.g. robot_trajectory)
	//
	// We use that fact as a quick way to decide certain path ids

	int len = id_.length();

	if (len >= 12 && id_.substr(len - 11) == "_trajectory")
	{
		edge_type_ = TRAJECTORY_EDGE;
	}
	else
	{
		edge_type_ = OBSTACLE_EDGE;
	}
}

void SvgParser::path_move_to(double x, double y, const tag::coordinate::absolute &) {
	
	// We rely on SvgParser::set(const tag::attribute::id &, const boost::iterator_range<const char *> &) to
	// set the edge_type based on the id received, but not all paths have ids.
	//
	// If no id was created, interpret the next edge as an obstacle edge
	if (id_ == "")
		edge_type_ = OBSTACLE_EDGE;

	Vec start_point = (*transform_handler_)({x, y});

	switch (edge_type_)
	{
		case OBSTACLE_EDGE:

			obstacle_ = make_unique<Obstacle>(start_point);
			
			// Associate ID if it exists
			if (id_ != "")
				obstacle_->setId(std::move(id_));

			break;

		case TRAJECTORY_EDGE:

			trajectory_intermediate_points_ = {start_point};

			break;
	}
}


void SvgParser::path_exit() {

	switch (edge_type_)
	{
		case OBSTACLE_EDGE:
		{

			// Enforce closure of obstacles (i.e. the path must start and end in the same place)
			const Vec & start = obstacle_->getStart();
			const Vec & end = obstacle_->getEnd();
			if (start != end)
			{
				unique_ptr<ObstacleEdge> new_edge {new LinearEdge(end, start)};
				obstacle_->add_edge(std::move(new_edge));
			}

			// Add obstacle_ to world
			world.addObstacle(std::move(obstacle_));

			break;
		}
		case TRAJECTORY_EDGE:
		{

			// Clip "_trajectory" off of the end of the id
			string clipped_id = id_.substr(0, id_.length() - 11);
			
			// Construct container for trajectory info and append it to master list
			trajectory_init_param_lists_.push_back(
				make_pair<string, vector<Vec>>(
					std::move(clipped_id),
					std::move(trajectory_intermediate_points_)
				)
			);

			break;
		}
	}

	// Reset path-tracking state in order be prepared for the next obstacle
	id_ = "";
	obstacle_ = nullptr;
	trajectory_intermediate_points_.clear();
}
/* ====================================================================================================== */



/* =========================================== Edge detection =========================================== */
void SvgParser::path_line_to(double x, double y, const tag::coordinate::absolute &) {

	// Transform coordinates
	Vec end = (*transform_handler_)({x, y}); 

	switch (edge_type_)
	{
		case OBSTACLE_EDGE:
		{
			unique_ptr<ObstacleEdge> new_edge {new LinearEdge(obstacle_->getEnd(), end)};

			obstacle_->add_edge(std::move(new_edge));

			break;
		}
		case TRAJECTORY_EDGE:
		{
			trajectory_intermediate_points_.push_back(end);

			break;
		}
	}
}

void SvgParser::path_cubic_bezier_to(double x1, double y1,
				     double x2, double y2,
				     double x, double y,
				     const tag::coordinate::absolute &) {

	// Transformed end point is necessary for both OBSTACLE_EDGE and TRAJECTORY_EDGE
	//
	// If it is a obstacle edge, we will need to transform the control points as well
	Vec end = (*transform_handler_)({x, y}); 

	switch (edge_type_)
	{
		case OBSTACLE_EDGE:
		{
			// Transform coordinates
			Vec control_1 = (*transform_handler_)({x1, y1}); 
			Vec control_2 = (*transform_handler_)({x2, y2}); 

			unique_ptr<ObstacleEdge> new_edge {new CubicBezierEdge(obstacle_->getEnd(), control_1, control_2, end)};

			obstacle_->add_edge(std::move(new_edge));

			break;
		}
		case TRAJECTORY_EDGE:
		{
			
			trajectory_intermediate_points_.push_back(end);

			break;
		}
	}
}

// TODO: Implement QuadraticBezierEdge and EllipticalArcEdge classes, then generate objects here

void SvgParser::path_quadratic_bezier_to(double x1, double y1,
					 double x, double y,
					 const tag::coordinate::absolute &)
{ }

void SvgParser::path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
				       bool large_arc_flag, bool sweep_flag,
				       double x, double y,
				       const tag::coordinate::absolute &)
{ }
/* ====================================================================================================== */



/* ========================================= Trajectory handling ======================================== */
void SvgParser::associateTrajectories() {

	int failures = 0;

	for (auto && trajectory_init_param_list : trajectory_init_param_lists_)
	{
		const string & associated_path = trajectory_init_param_list.first;

		// Not const because we might need to modify it if it is an obstacle trajectory
		vector<Vec> &  intermediate_points = trajectory_init_param_list.second;

		if (associated_path == "robot")
		{
			world.setRobotTrajectory(constructTrajectory(intermediate_points));
		}
		else
		{
			auto obstacle_itr = world.findObstacle(associated_path);

			if (obstacle_itr != world.obstacles.end())
			{
				
				// Obstacle trajectories should really be interpretted as a cumulative offset from the origin point
				//
				// As such, translating the trajectory around the world shouldn't really make a difference.
				// We should subtract each of the intermediate points by the first point so that the intermediate
				// points represent offsets, not absolute positions
				const Vec trajectory_start = intermediate_points.front();
				for (Vec & point : intermediate_points)
				{
					point -= trajectory_start;
				}

				unique_ptr<Trajectory> trajectory = constructTrajectory(intermediate_points);
				(*obstacle_itr)->setTrajectory(std::move(trajectory));
			}
			else
			{
				cout << "Encountered path with id = \"" << associated_path <<
					"_trajectory\" but couldn't find an existing obstacle with id = " << associated_path << endl;
				++failures;
			}
		}
	}

	if (failures > 0)
		exit(-1);
}

unique_ptr<Trajectory> SvgParser::constructTrajectory(const vector<Vec> & intermediate_points) {
	
	vector<Pose> intermediate_poses;

	double theta;
	for (int i = 0; i < intermediate_points.size() - 1; ++i) {

		const Vec & p1 = intermediate_points[i];
		const Vec & p2 = intermediate_points[i + 1];

		theta = (p2 - p1).radians();
		
		intermediate_poses.push_back({p1, theta});
	}
	intermediate_poses.push_back({intermediate_points.back(), theta});

	return make_unique<Trajectory>(intermediate_poses);
}

/* ====================================================================================================== */
