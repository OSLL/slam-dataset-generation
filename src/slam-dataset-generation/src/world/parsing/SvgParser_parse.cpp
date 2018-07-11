#include "world/parsing/SvgParser.h"
#include <string>
#include <iostream>
#include <fstream>

#include <svgpp/svgpp.hpp>

// XML policy includes
#include <rapidxml_ns/rapidxml_ns.hpp>
#include <svgpp/policy/xml/rapidxml_ns.hpp>

// Customize svgpp with custom policies
#include "world/parsing/AttributeTraversalPolicy.h"

using std::ifstream;
using std::istreambuf_iterator;
using std::cout;
using std::endl;
using std::string;
using boost::mpl::pair;
using boost::mpl::set;
using namespace svgpp;

// Define processable elements in svg
typedef set<
	tag::element::svg,
	tag::element::g,
	tag::element::path
>::type processed_elements_t;

// Define processable attributes in svg elements
typedef set<
	// Transform
	tag::attribute::transform,

	// Viewport
	tag::attribute::x,
	tag::attribute::y,
	tag::attribute::width,
	tag::attribute::height,
	tag::attribute::viewBox,
	tag::attribute::preserveAspectRatio,

	// Path
	pair<tag::element::path, tag::attribute::id>,
	pair<tag::element::path, tag::attribute::d>
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

	// If XML root node found, parse SVG
	if (svg_root) {
		SvgParser parsing_context(world);

		document_traversal<
			processed_elements<processed_elements_t>,
			processed_attributes<processed_attributes_t>,
			viewport_policy<policy::viewport::as_transform>,
			length_policy<policy::length::forward_to_method<SvgParser, const LengthFactory>>,
			attribute_traversal_policy<AttributeTraversalPolicy>
		>::load_document(svg_root, parsing_context);
	} else {
		cout << "Could not extract svg root node from file." << endl;
		exit(-1);
	}
}
