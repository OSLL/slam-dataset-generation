#ifndef WORLD_PARSING_ATTRIBUTETRAVERSALPOLICY_H
#define WORLD_PARSING_ATTRIBUTETRAVERSALPOLICY_H

#include "svgpp/policy/attribute_traversal.hpp"

struct AttributeTraversalPolicy
	: public svgpp::policy::attribute_traversal::default_policy
{
	static const bool parse_style = false;
	static const bool css_hides_presentation_attribute = false;
};

#endif
