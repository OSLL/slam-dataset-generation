#include "world/parsing/SvgParser.h"

#include <string>
#include <iostream>
#include <fstream>

// Svgpp
#include <svgpp/svgpp.hpp>
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>

// Customize svgpp with custom policies
#include "world/parsing/LengthFactory.h"
#include "world/parsing/AttributeTraversalPolicy.h"

using std::ifstream;
using std::istreambuf_iterator;
using std::cout;
using std::endl;
using std::string;

// Define processable elements in svg
typedef boost::mpl::set<
	svgpp::tag::element::svg,
	svgpp::tag::element::g,
	svgpp::tag::element::path
>::type processed_elements_t;

// Define processable attributes in svg elements
typedef boost::mpl::set<
	// Transform
	svgpp::tag::attribute::transform,

	// Viewport
	svgpp::tag::attribute::x,
	svgpp::tag::attribute::y,
	svgpp::tag::attribute::width,
	svgpp::tag::attribute::height,
	svgpp::tag::attribute::viewBox,
	svgpp::tag::attribute::preserveAspectRatio,

	// Path
	boost::mpl::pair<svgpp::tag::element::path, svgpp::tag::attribute::id>,
	boost::mpl::pair<svgpp::tag::element::path, svgpp::tag::attribute::d>
>::type processed_attributes_t;

// Define what an xml element is for svgpp
typedef rapidxml_ns::xml_node<> const * xml_element_t;

void SvgParser::parse(const char * filename, World & world) {

	// Dump file into char buffer
	ifstream file(filename);
	if (!file.good())
	{
		cout << "Problem opening file at " << filename << "..." << endl;
		exit(-1);
	}
	string file_contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	char * buffer = (char *)file_contents.c_str();


	// Parse XML
	rapidxml_ns::xml_document<> doc;
	doc.parse<0>(buffer);
	rapidxml_ns::xml_node<> * svg_root = doc.first_node("svg");

	// If XML root node couldn't be found found, exit
	if (!svg_root) {
		cout << "Could not extract svg root node from file." << endl;
		exit(-1);
	}

	SvgParser parsing_context(world);

	svgpp::document_traversal<
		svgpp::processed_elements<processed_elements_t>,
		svgpp::processed_attributes<processed_attributes_t>,
		svgpp::viewport_policy<svgpp::policy::viewport::as_transform>,
		svgpp::length_policy<svgpp::policy::length::forward_to_method<SvgParser, const LengthFactory>>,
		svgpp::attribute_traversal_policy<AttributeTraversalPolicy>
	>::load_document(svg_root, parsing_context);

	parsing_context.associateTrajectories();
}
