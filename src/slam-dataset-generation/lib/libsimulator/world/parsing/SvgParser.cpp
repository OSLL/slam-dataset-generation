#include "world/parsing/SvgParser.h"

#include <string>
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

using namespace svgpp;

// Obstacle edge types
#include "obstacle/ObstacleEdge.h"
#include "obstacle/LinearEdge.h"
#include "obstacle/CubicBezierEdge.h"

SvgParser::SvgParser(World & world_ref)
	: world(world_ref)
	, current_path(nullptr)
	, viewport_location(-1, -1)
{ }

/* ======================================== Document information ======================================== */
void SvgParser::set_viewport(double x, double y, double width, double height) {
	viewport_location = {x, viewport_height - y};
	viewport_width = width;
	viewport_height = height;

	// Inform transform handler of viewport height
	transform_handler_.setViewportHeight(viewport_height);
}

void SvgParser::set_viewbox_size(double width, double height) {
	viewbox_width = width;
	viewbox_height = height;
}
/* ====================================================================================================== */



/* ========================================= Transform Handling ========================================= */
void SvgParser::transform_matrix(const SvgTransformHandler::Transform & t) {
	transform_handler_.receiveTransform(t);
}

void SvgParser::on_enter_element(const tag::element::any &) {
	transform_handler_.enterElement();
}

void SvgParser::on_exit_element() {
	transform_handler_.exitElement();
}
/* ====================================================================================================== */



/* =========================================== Path detection =========================================== */
void SvgParser::set(const tag::attribute::id &, const boost::iterator_range<const char *> & value) {
	id_.assign(boost::begin(value), boost::end(value));
}

void SvgParser::path_move_to(double x, double y, const tag::coordinate::absolute &) {
	Vec start_point = transform_handler_({x, y});

	temporary_obstacle_ = make_shared<Obstacle>(start_point);

	// If an id was found, assign it to the obstacle
	temporary_obstacle->setId(id_);
}

void SvgParser::path_exit() {


	
	// Path processing is complete.  Move temporary_obstacle_ to the world

	world.

	// Reset 
}
/* ====================================================================================================== */



/* =========================================== Edge detection =========================================== */
void SvgParser::path_line_to(double x, double y, const tag::coordinate::absolute &) {
	// Determine which path this edge should be added to
	Obstacle * current_path = world.all_obstacles.back();

	// Transform coordinates
	Vec end = transform_handler_({x, y}); 

	// Add edge
	ObstacleEdge * new_edge = new LinearEdge(current_path->end(), end);
	current_path->add_edge(new_edge);
}

void SvgParser::path_cubic_bezier_to(double x1, double y1,
					  double x2, double y2,
					  double x, double y,
					  const tag::coordinate::absolute &) {
	// Determine which path this edge should be added to
	Obstacle * current_path = world.all_obstacles.back();

	// Transform coordinates
	Vec control_1 = transform_handler_({x1, y1}); 
	Vec control_2 = transform_handler_({x2, y2}); 
	Vec end = transform_handler_({x, y}); 

	// Add edge
	ObstacleEdge * new_edge = new CubicBezierEdge(current_path->end(), control_1, control_2, end);
	current_path->add_edge(new_edge);
}

// TODO: Implement QuadraticBezierEdge and EllipticalArcEdge classes, then generate objects here

void SvgParser::path_quadratic_bezier_to(double x1, double y1,
					      double x, double y,
					      const tag::coordinate::absolute &) { }

void SvgParser::path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
					    bool large_arc_flag, bool sweep_flag,
					    double x, double y,
					    const tag::coordinate::absolute &) { }
/* ====================================================================================================== */
