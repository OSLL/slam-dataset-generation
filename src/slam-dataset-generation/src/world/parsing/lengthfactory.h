#ifndef LENGTHFACTORY_H
#define LENGTHFACTORY_H

#include <svgpp/svgpp.hpp>

class ParsingContext;

struct LengthFactory {
	
	typedef double length_type;
	typedef double number_type;

	LengthFactory(const ParsingContext & parent_val);

	const ParsingContext & parent;

	length_type create_length(number_type number, svgpp::tag::length_units::em) const;
	length_type create_length(number_type number, svgpp::tag::length_units::ex) const;
	length_type create_length(number_type number, svgpp::tag::length_units::px) const;
	length_type create_length(number_type number, svgpp::tag::length_units::in) const;
	length_type create_length(number_type number, svgpp::tag::length_units::cm) const;
	length_type create_length(number_type number, svgpp::tag::length_units::mm) const;
	length_type create_length(number_type number, svgpp::tag::length_units::pt) const;
	length_type create_length(number_type number, svgpp::tag::length_units::pc) const;
	length_type create_length(number_type number, svgpp::tag::length_units::none) const;

	length_type create_length(number_type number, svgpp::tag::length_units::percent, svgpp::tag::length_dimension::width) const;
	length_type create_length(number_type number, svgpp::tag::length_units::percent, svgpp::tag::length_dimension::height) const;
	length_type create_length(number_type number, svgpp::tag::length_units::percent, svgpp::tag::length_dimension::not_width_nor_height) const;

	length_type length_to_user_coordinate(number_type number, svgpp::tag::length_dimension::width) const;
	length_type length_to_user_coordinate(number_type number, svgpp::tag::length_dimension::height) const;
};

#include "world/parsing/parsingcontext.h"

#endif
