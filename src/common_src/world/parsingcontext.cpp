#include "world/parsingcontext.h"
#include <string>
#include <iostream>
#include <cstdio>

// Svgpp xml parsing includes
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>

// Edge types
#include "edge/edge.h"
#include "edge/linearedge.h"
#include "edge/cubicbezieredge.h"

using namespace svgpp;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using boost::mpl::pair;

// Define processable elements in svg
typedef boost::mpl::set<
//	tag::element::svg,
	tag::element::g,
	tag::element::path
>::type processed_elements_t;

// Define processable attributes in svg elements
typedef boost::mpl::insert<
	traits::shapes_attributes_by_element,
	tag::attribute::id,
//	pair<tag::element::path, tag::attribute::id>,
	tag::attribute::transform
>::type processed_attributes_t;

// xml_element_t typedef
typedef rapidxml_ns::xml_node<> const * xml_element_t;


ParsingContext::ParsingContext(World & parent_obj) :
	parent(parent_obj),
	current_path(nullptr),
	parsing_path(false),
	transformation_matrix({1, 0, 0, 0, 1, 0}) // identity matrix
{ }

void ParsingContext::parse(char * buffer) {
	// Use rapidxml to parse svg and find root node
	rapidxml_ns::xml_document<> doc;
	doc.parse<0>(buffer);
	rapidxml_ns::xml_node<> * svg_root = doc.first_node("svg");

	// If root node of svg was found, traverse the svg to populate World
	if (svg_root) {
		document_traversal<
			processed_elements<processed_elements_t>,
			processed_attributes<processed_attributes_t>
		>::load_document(svg_root, *this);
	} else {
		cout << "Could not extract svg root node from file." << endl;
	}
}



/* ########################### Keep track of path ids ############################# */
void ParsingContext::set(tag::attribute::id, const boost::iterator_range<const char *> & value) {

	// Associate id with path
	if (parsing_path) {

		// Harvest id from weird container
		string id;
		id.assign(boost::begin(value), boost::end(value));

		// Obtain pointer to constructed path
		EdgePath * last_constructed_path = parent.all_obstacles.back();
		
		// Set id
		last_constructed_path->id = id;
	}
}
/* #################################################################################*/




/* ###################### Determine beginning and end of path ######################*/
void ParsingContext::path_move_to(double x, double y, tag::coordinate::absolute) {
	parsing_path = true;
	EdgePath * new_path = new EdgePath({x, y});
	parent.all_obstacles.push_back(new_path);
}

void ParsingContext::on_exit_element() {
	if (parsing_path) {
		// Obtain pointer to recently constructed EdgePath
		EdgePath * last_constructed_path = parent.all_obstacles.back();

		// Ensure that closure of paths is enforced
		const Vec & path_start = last_constructed_path->start;
		const Vec & path_end = last_constructed_path->end();
		if (path_start != path_end) {
			Edge * new_edge = new LinearEdge(path_end, path_start);
			last_constructed_path->add_edge(new_edge);
		}

		// Place a reference to the constructed path in the correct location
		if (last_constructed_path->id == "world_boundary") {
			parent.world_boundary = last_constructed_path;
		} else {
			parent.interior_obstacles.push_back(last_constructed_path);
		}

		// We are no longer parsing a path
		parsing_path = false;
	}
}
/* ################################################################################ */



/* ####################### Handling coordinate tranformation ###################### */
void ParsingContext::transform_matrix(const boost::array<double, 6> & matrix) {
	transformation_matrix = matrix;
}

Vec ParsingContext::transform(const Vec & v) {
	boost::array<double, 6> & a = transformation_matrix;
	return {a[0]*v.x + a[1]*v.y + a[2], a[3]*v.x + a[4]*v.y + a[5]};
}
/* ################################################################################ */



/* ################################ Add edges ##################################### */
void ParsingContext::path_line_to(double x, double y, tag::coordinate::absolute) {
	// Determine which path this edge should be added to
	EdgePath * current_path = parent.all_obstacles.back();

	// Transform coordinates
	Vec end = transform({x, y}); 

	// Add edge
	Edge * new_edge = new LinearEdge(current_path->end(), end);
	current_path->add_edge(new_edge);
}

void ParsingContext::path_cubic_bezier_to(double x1, double y1,
					  double x2, double y2,
					  double x, double y,
					  tag::coordinate::absolute) {
	// Determine which path this edge should be added to
	EdgePath * current_path = parent.all_obstacles.back();

	// Transform coordinates
	Vec control_1 = transform({x1, y1}); 
	Vec control_2 = transform({x2, y2}); 
	Vec end = transform({x, y}); 

	// Add edge
	Edge * new_edge = new CubicBezierEdge(current_path->end(), control_1, control_2, end);
	current_path->add_edge(new_edge);
}

// TODO: Implement QuadraticBezierEdge and EllipticalArcEdge classes, then generate objects here
void ParsingContext::path_quadratic_bezier_to(double x1, double y1,
					      double x, double y,
					      tag::coordinate::absolute) { }

void ParsingContext::path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
					    bool large_arc_flag, bool sweep_flag,
					    double x, double y,
					    tag::coordinate::absolute) { }
/* ################################################################################ */



/* ############################## Unneeded functions ############################## */
void ParsingContext::on_enter_element(tag::element::any) {}

void ParsingContext::path_exit() { }

void ParsingContext::path_close_subpath() { }
/* ################################################################################ */
