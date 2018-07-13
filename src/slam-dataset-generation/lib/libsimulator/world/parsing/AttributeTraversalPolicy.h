#ifndef WORLD_PARSING_ATTRIBUTETRAVERSALPOLICY_H
#define WORLD_PARSING_ATTRIBUTETRAVERSALPOLICY_H

#include "svgpp/policy/attribute_traversal.hpp"

struct AttributeTraversalPolicy : public svgpp::policy::attribute_traversal::default_policy
{
	// We don't need to know the style information for the SVG document, so we explicitly disable the parsing of it
	static const bool parse_style = false;
	static const bool css_hides_presentation_attribute = false;

	///*
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
	//*/

	/*
	typedef boost::mpl::if_<
		// Condition
		boost::mpl::has_key<
			boost::mpl::set<
				tag::element::svg,
				tag::element::symbol
			>,
			boost::mpl::_1
		>,
		
		// Value if condition is true
		boost::mpl::vector<
			// ... load viewport-related attributes first ...
			tag::attribute::x,
			tag::attribute::y,
			tag::attribute::width,
			tag::attribute::height,
			tag::attribute::viewBox,
			tag::attribute::preserveAspectRatio,
			// ... notify library, that all viewport attributes that are present was loaded.
			// It will result in call to BaseContext::set_viewport and BaseContext::set_viewbox_size
			notify_context<tag::event::after_viewport_attributes>
		>::type,
		
		// Value if condition is false
		boost::mpl::empty_sequence

	> get_priority_attributes_by_element;
	*/
};

#endif
