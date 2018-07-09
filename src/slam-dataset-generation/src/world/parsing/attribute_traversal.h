#ifndef ATTRIBUTE_TRAVERSAL_H
#define ATTRIBUTE_TRAVERSAL_H

#include "svgpp/policy/attribute_traversal.hpp"

struct custom_attribute_traversal_policy
	: public svgpp::policy::attribute_traversal::default_policy
{
	static const bool parse_style = false;
	static const bool css_hides_presentation_attribute = false;
};

#endif
