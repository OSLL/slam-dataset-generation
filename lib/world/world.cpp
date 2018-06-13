#include "world/world.h"
#include "misc/vec.h"
#include <svgpp/svgpp.hpp>
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::istreambuf_iterator;

using namespace svgpp;

// Define processable items in svg
typedef boost::mpl::set<
	tag::element::svg,
	tag::element::g,
//	tag::element::polygon,
//	tag::element::polyline,
//	tag::element::rect
//	tag::element::circle,
//	tag::element::ellipse,
	tag::element::line,
	tag::element::path
>::type processed_elements_t;

// Define processable tags in svg
typedef boost::mpl::insert<
	traits::shapes_attributes_by_element,
	tag::attribute::transform
>::type processed_attributes_t

// Define xml element tyepdef for svgpp
typedef rapidxml_ns::xml_node<> const * xml_element_t;

// Context for interfacing with svgpp
class Context {
	private:
		World & parent;
	public:
		Context(World & parent_obj) : parent(parent_obj) {}

		void on_enter_element(tag::element::any) {}
		void on_exit_element() {}
		void path_close_subpath() {}
		void path_exit() {}
		void path_move_to(double x, double y, tag::coordinate::absolute) {
			cout << "Move to " << Vec(x, y) << endl;

		}
		void path_line_to(double x, double y, tag::coordinate::absolute) {
			cout << "Line to " << Vec(x, y) << endl;
		}
		void path_cubic_bezier_to(double x1, double y1,
					  double x2, double y2,
					  double x, double y,
					  tag::coordinate::absolute) {
			cout << "Cubic bezier to " << Vec(x, y) << " with control points " << Vec(x1, y1) << ", " << Vec(x2, y2) << endl;
		}

		// Currently disabled
		void path_quadratic_bezier_to(double x1, double y1,
					      double x, double y,
					      tag::coordinate::absolute) {}
		void path_elliptical_arc_to(double rx, double ry, double x_axis_rotation,
					    bool large_arc_flag, bool sweep_flag,
					    double x, double y,
					    tag::coordinate::absolute) {}
};

World::World() :
	width(-1),
	height(-1)
{ }

void World::read_from_disk(const char * source) {
	// Check if file can be read
	ifstream file (source);
	if (!file.good()) {
		cout << "Problem opening file at " << source << "...\n";
		exit(-1);
	}

	// Dump file into char buffer
	string file_contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	char * buffer = (char *)file_contents.c_str();

	// Parse document
	rapidxml_ns::xml_document<> doc;
	doc.parse<0>(buffer);
	Context parsing_context(*this);
	rapidxml_ns::xml_node<> * svg = doc.first_node("svg");
	if (svg) {
		document_traversal<
			processed_elements<processed_elements_t>,
			processed_attributes<processed_attributes_t>
		>::load_document(svg, parsing_context);
	} else {
		cout << "Could not extract root node from svg." << endl;
	}
}

// Generate svg file from current world and write to destination
void World::write_to_disk(const char * destination) {
	// Not implemented
}
