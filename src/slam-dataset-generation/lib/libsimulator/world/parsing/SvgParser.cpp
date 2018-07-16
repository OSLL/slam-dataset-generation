#include "world/parsing/SvgParser.h"
#include "world/World.h"

#include <string>
#include <iostream>
#include <cstdio>

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::unique_ptr;
using std::make_unique;

using namespace svgpp;

// Obstacle edge types
#include "obstacle/ObstacleEdge.h"
#include "obstacle/LinearEdge.h"
#include "obstacle/CubicBezierEdge.h"

SvgParser::SvgParser(World & world_ref)
	: world(world_ref)
{ }

/* ======================================== Document information ======================================== */
void SvgParser::set_viewport(double x, double y, double width, double height) {
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

	obstacle_ = make_unique<Obstacle>(start_point);

	if (id_ != "")
	{
		obstacle_->setId(std::move(id_));
	}
}

void SvgParser::path_exit() {
	
	// Selectively enforce closure
	if (obstacle_->getId() != "linear_trajectory")
	{
		const Vec & start = obstacle_->getStart();
		const Vec & end = obstacle_->getEnd();
		
		// Note that operator==(const Vec &, const Vec &) ensures the x's and y's fall within a certain epsilon, so as to avoid double rounding errors
		if (start != end)
		{
			unique_ptr<ObstacleEdge> new_edge {new LinearEdge(end, start)};
			obstacle_->add_edge(std::move(new_edge));
		}
	}

	// Path processing is complete.  Move obstacle_ to the world
	world.addObstacle(std::move(obstacle_));

	// Reset local obstacle state in order be prepared for the next obstacle
	id_ = "";
	obstacle_ = nullptr;
}
/* ====================================================================================================== */



/* =========================================== Edge detection =========================================== */
void SvgParser::path_line_to(double x, double y, const tag::coordinate::absolute &) {

	// Transform coordinates
	Vec end = transform_handler_({x, y}); 

	// Add edge
	unique_ptr<ObstacleEdge> new_edge {new LinearEdge(obstacle_->getEnd(), end)};
	obstacle_->add_edge(std::move(new_edge));
}

void SvgParser::path_cubic_bezier_to(double x1, double y1,
				     double x2, double y2,
				     double x, double y,
				     const tag::coordinate::absolute &) {

	// Transform coordinates
	Vec control_1 = transform_handler_({x1, y1}); 
	Vec control_2 = transform_handler_({x2, y2}); 
	Vec end = transform_handler_({x, y}); 

	// Add edge
	unique_ptr<ObstacleEdge> new_edge {new CubicBezierEdge(obstacle_->getEnd(), control_1, control_2, end)};
	obstacle_->add_edge(std::move(new_edge));
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
