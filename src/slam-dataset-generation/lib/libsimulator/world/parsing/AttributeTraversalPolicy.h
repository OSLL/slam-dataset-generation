#ifndef WORLD_PARSING_ATTRIBUTETRAVERSALPOLICY_H
#define WORLD_PARSING_ATTRIBUTETRAVERSALPOLICY_H

#include "svgpp/policy/attribute_traversal.hpp"

struct AttributeTraversalPolicy : public svgpp::policy::attribute_traversal::default_policy
{
	// We don't need to know the style information for the SVG document, so we explicitly disable the parsing of it
	static const bool parse_style = false;
	static const bool css_hides_presentation_attribute = false;

	typedef boost::mpl::if_<
		// Condition
		boost::mpl::has_key<
			boost::mpl::set<
				svgpp::tag::element::path
			>,
			boost::mpl::_1
		>,

		// Value if condition is true
		boost::mpl::vector<
			svgpp::tag::attribute::id
		>::type,

		// Value if condition is false
		boost::mpl::empty_sequence
	> get_priority_attributes_by_element;
};

#endif
