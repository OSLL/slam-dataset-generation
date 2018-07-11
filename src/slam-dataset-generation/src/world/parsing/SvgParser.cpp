#include "world/parsing/SvgParser.h"

#include <string>
#include <iostream>
#include <cstdio>

#include <svgpp/definitions.hpp>

using std::cout;
using std::endl;
using std::string;
using std::ostream;

using namespace svgpp;

// Edge types
#include "edge/edge.h"
#include "edge/linearedge.h"
#include "edge/cubicbezieredge.h"

static const Matrix identity_matrix {1, 0, 0, 1, 0, 0};

SvgParser::SvgParser(World & world_ref) :
	world(world_ref),
	current_path(nullptr),
	parsing_path(false),
	current_transform_matrix(identity_matrix),
	viewport_location(-1, -1),
	length_factory_(*this)
{ }

/* ======================================== Document information ======================================== */
void SvgParser::set_viewport(double x, double y, double width, double height) {
	viewport_location = {x, viewport_height - y};
	viewport_width = width;
	viewport_height = height;
}

void SvgParser::set_viewbox_size(double width, double height) {
	viewbox_width = width;
	viewbox_height = height;
}
/* ====================================================================================================== */



/* =========================================== Path detection =========================================== */
void SvgParser::path_move_to(double x, double y, tag::coordinate::absolute) {
	parsing_path = true;
	EdgePath * new_path = new EdgePath(transform({x, y}));
	world.all_obstacles.push_back(new_path);
}

void SvgParser::on_exit_element() {
	if (parsing_path) {
		// Obtain pointer to recently constructed EdgePath
		EdgePath * last_constructed_path = world.all_obstacles.back();

		// Selectively enforce closure of paths
		if (last_constructed_path->id != "linear_trajectory") {
			const Vec & path_start = last_constructed_path->start;
			const Vec & path_end = last_constructed_path->end();

			if (path_start != path_end) {
				Edge * new_edge = new LinearEdge(path_end, path_start);
				last_constructed_path->add_edge(new_edge);
			}
		}

		// Place a reference to the constructed path in the correct location
		if (last_constructed_path->id == "world_boundary") {
			world.world_boundary = last_constructed_path;
		} else {
			world.interior_obstacles.push_back(last_constructed_path);
		}

		// We are no longer parsing a path
		parsing_path = false;
	}

	// Remove transform
	pop_transform();
}

void SvgParser::set(tag::attribute::id &, const boost::iterator_range<const char *> & value) {

	// Associate id with path
	if (parsing_path) {

		// Harvest id from weird container
		string id;
		id.assign(boost::begin(value), boost::end(value));

		// Obtain pointer to constructed path
		EdgePath * last_constructed_path = world.all_obstacles.back();
		
		// Set id
		last_constructed_path->id = id;
	}
}
/* ====================================================================================================== */



/* =========================================== Edge detection =========================================== */
void SvgParser::path_line_to(double x, double y, tag::coordinate::absolute) {
	// Determine which path this edge should be added to
	EdgePath * current_path = world.all_obstacles.back();

	// Transform coordinates
	Vec end = transform({x, y}); 

	// Add edge
	Edge * new_edge = new LinearEdge(current_path->end(), end);
	current_path->add_edge(new_edge);
}

void SvgParser::path_cubic_bezier_to(double x1, double y1,
					  double x2, double y2,
					  double x, double y,
					  tag::coordinate::absolute) {
	// Determine which path this edge should be added to
	EdgePath * current_path = world.all_obstacles.back();

	// Transform coordinates
	Vec control_1 = transform({x1, y1}); 
	Vec control_2 = transform({x2, y2}); 
	Vec end = transform({x, y}); 

	// Add edge
	Edge * new_edge = new CubicBezierEdge(current_path->end(), control_1, control_2, end);
	current_path->add_edge(new_edge);
}

// TODO: Implement QuadraticBezierEdge and EllipticalArcEdge classes, then generate objects here

void SvgParser::path_quadratic_bezier_to(double x1, double y1,
					      double x, double y,
					      tag::coordinate::absolute) { }

void SvgParser::path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
					    bool large_arc_flag, bool sweep_flag,
					    double x, double y,
					    tag::coordinate::absolute) { }
/* ====================================================================================================== */



/* ========================================= Transform Handling ========================================= */

ostream & operator<<(ostream & o, const Matrix & m) {
	printf(
		"\n"
		"[%f, %f, %f]\n"
		"[%f, %f, %f]\n"
		"[%f, %f, %f]\n",
		m[0], m[2], m[4],
		m[1], m[3], m[5],
		0.0f, 0.0f, 1.0f
	);
	return o;
}
static Matrix multiply_matrix(const Matrix & m1, const Matrix & m2) {
	Matrix result;

	int a = 0;
	int b = 1;
	int c = 2;
	int d = 3;
	int e = 4;
	int f = 5;

	result[a] = m1[a]*m2[a] + m1[c]*m2[b];		// a = a1*a2 + c1*b2
	result[b] = m1[b]*m2[a] + m1[d]*m2[b];		// b = b1*a2 + d1*b2
	result[c] = m1[a]*m2[c] + m1[c]*m2[d];		// c = a1*c2 + c1*d2
	result[d] = m1[b]*m2[c] + m1[d]*m2[d];		// d = b1*c2 + d1*d2
	result[e] = m1[a]*m2[e] + m1[c]*m2[f] + m1[e];  // e = a1*e2 + c1*f2 + e1
	result[f] = m1[b]*m2[e] + m1[d]*m2[f] + m1[f];	// f = b1*e2 + d1*f2 + f1

	return result;
}

void SvgParser::push_identity_transform() {
	transform_matrices.push_back(identity_matrix);
}

void SvgParser::pop_transform() {
	// If last matrix in transform_matrices isn't the identity matrix, update transform_matrix
	const Matrix & last_matrix = transform_matrices.back();
	if (last_matrix != Matrix{1, 0, 0, 1, 0, 0}) {

		transform_matrices.pop_back();

		// The best thing to do scaling wise would be to find the inverse of this matrix and multiply
		// transform_matrix by it.  However, that would take a lot of code.
		//
		// For now, I just multiple all the prior matrices together to get the new transformation_matrix
		current_transform_matrix = identity_matrix;
		for (const Matrix & m : transform_matrices) {
			current_transform_matrix = multiply_matrix(current_transform_matrix, m);
		}
	} else {
		transform_matrices.pop_back();
	}
}

void SvgParser::transform_matrix(const Matrix & m) {
	// When we entered the current element, we pushed on an identity matrix
	// We need to copy this matrix into that one
	if (transform_matrices.size() != 0) {
		transform_matrices.back() = m;
	} else {
		transform_matrices.push_back(m);
	}

	current_transform_matrix = multiply_matrix(current_transform_matrix, m);
}

Vec SvgParser::transform(const Vec & v) {
	// Create succinct reference for transformation matrix
	const Matrix & m = current_transform_matrix;

	// Transform vector relative to current  viewport
	Vec result {m[0]*v.x + m[2]*v.y + m[4], m[1]*v.x + m[3]*v.y + m[5]};

	// Flip y coordinate so that the axis system is like a traditional cartesian coordinate system
	result.y = viewport_height - result.y;

	return result;
}


void SvgParser::on_enter_element(tag::element::any) {
	// Push on an identity matrix onto the stack of transformation matrices
	// If the element actually contains a transform, SvgParser::transform_matrix will correct it
	push_identity_transform();
}
/* ====================================================================================================== */
