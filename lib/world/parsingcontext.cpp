#include "world/parsingcontext.h"
#include "world/linearedge.h"
#include "world/bezieredge.h"
#include <string>
#include <iostream>
#include <cstdio>
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>

using namespace svgpp;
using std::cout;
using std::endl;
using std::string;
using std::ostream;

// Define processable elements in svg
typedef boost::mpl::set<
//	tag::element::svg,
	tag::element::g,
	tag::element::path
>::type processed_elements_t;

// Define processable attributes in svg elements
typedef boost::mpl::insert<
	traits::shapes_attributes_by_element,
	tag::attribute::id
>::type processed_attributes_t;

// xml_element_t typedef
typedef rapidxml_ns::xml_node<> const * xml_element_t;


ParsingContext::ParsingContext(World & parent_obj) :
	parent(parent_obj),
	current_path(nullptr),
	parsing_path(false)
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



/* ########################### Keep track of path ids ##############################*/
void ParsingContext::set(tag::attribute::id, const boost::iterator_range<const char *> & value) {

	// Associate id with path
	if (parsing_path) {

		// Harvest id from weird container
		string id;
		id.assign(boost::begin(value), boost::end(value));

		// Obtain pointer to constructed path
		Path * last_constructed_path = parent.all_obstacles.back();
		
		// Set id
		last_constructed_path->set_id(id);

		cout << "path detected with id = " << id << endl;
	}
}
/* #################################################################################*/




/* ###################### Determine beginning and end of path ######################*/
void ParsingContext::path_move_to(double x, double y, tag::coordinate::absolute) {
	parsing_path = true;
	Path * new_path = new Path({x, y});
	parent.all_obstacles.push_back(new_path);
}

void ParsingContext::on_exit_element() {
	if (parsing_path) {
		// Obtain pointer to constructed path
		Path * last_constructed_path = parent.all_obstacles.back();

		// Ensure that closure of paths is enforced
		const Vec & path_start = last_constructed_path->start();
		const Vec & path_end = last_constructed_path->end();
		if (path_start != path_end) {
			Edge * new_edge = new LinearEdge(path_end, path_start);
			last_constructed_path->add_edge(new_edge);
		}

		// Place a reference to the constructed path in the correct location
		if (last_constructed_path->id() == "world_boundary") {
			parent.world_boundary = last_constructed_path;
		} else {
			parent.interior_obstacles.push_back(last_constructed_path);
		}

		// We are no longer parsing a path
		parsing_path = false;
	}
}
/* ################################################################################# */



/* ############################### Add edges ####################################### */
void ParsingContext::path_line_to(double x, double y, tag::coordinate::absolute) {
	// Determine which path this edge should be added to
	Path * current_path = parent.all_obstacles.back();

	// Add edge
	Edge * new_edge = new LinearEdge(current_path->end(), {x, y});
	current_path->add_edge(new_edge);
}

void ParsingContext::path_cubic_bezier_to(double x1, double y1,
			  double x2, double y2,
			  double x, double y,
			  tag::coordinate::absolute) {
	// Determine which path this edge should be added to
	Path * current_path = parent.all_obstacles.back();

	// Add edge
	Edge * new_edge = new BezierEdge(current_path->end(), {x1, y1}, {x2, y2}, {x, y});
	current_path->add_edge(new_edge);
}

// TODO: Implement QuadraticBezierEdge and EllipticalArcEdge classes, then generate objects here
void ParsingContext::path_quadratic_bezier_to(double x1, double y1,
			      double x, double y,
			      tag::coordinate::absolute) {
      	//
}

void ParsingContext::path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
			    bool large_arc_flag, bool sweep_flag,
			    double x, double y,
			    tag::coordinate::absolute) {
	//
}
/* #################################################################################### */



/* ############################## Unneeded functions ################################## */
void ParsingContext::on_enter_element(tag::element::any) {}

void ParsingContext::path_exit() { }

void ParsingContext::path_close_subpath() { }
/* #################################################################################### */
