#include "world/parsing/lengthfactory.h"
#include <iostream>

typedef LengthFactory::length_type length_type;
typedef LengthFactory::number_type number_type;

using namespace svgpp;
using std::cout;
using std::endl;

LengthFactory::LengthFactory(const ParsingContext & parent_val) :
	parent(parent_val)
{ }

length_type LengthFactory::create_length(number_type number, tag::length_units::em) const {
	cout << "Units em used to specify length.  Cannot convert." << endl;
	exit(-1);
}

length_type LengthFactory::create_length(number_type number, tag::length_units::ex) const {
	cout << "Units ex used to specify length.  Cannot convert." << endl;
	exit(-1);
}

length_type LengthFactory::create_length(number_type number, tag::length_units::px) const {
	cout << "Units px used to specify length.  Cannot convert." << endl;
	exit(-1);
}

length_type LengthFactory::create_length(number_type number, tag::length_units::pc) const {
	cout << "Units pc used to specify length.  Cannot convert." << endl;
	exit(-1);
}

length_type LengthFactory::create_length(number_type number, tag::length_units::pt) const {
	cout << "Units pt used to specify length.  Cannot convert." << endl;
	exit(-1);
}

length_type LengthFactory::create_length(number_type number, tag::length_units::none) const {
	return number;
}

length_type LengthFactory::create_length(number_type number, tag::length_units::in) const {
	return number / 39.3701;
}

length_type LengthFactory::create_length(number_type number, tag::length_units::cm) const {
	return number / 100.0;
}

length_type LengthFactory::create_length(number_type number, tag::length_units::mm) const {
	return number / 1000.0;
}


length_type LengthFactory::create_length(number_type number, tag::length_units::percent, tag::length_dimension::width) const {
	cout << "Converting " << number << "% of width" << endl;
	return number;
}

length_type LengthFactory::create_length(number_type number, tag::length_units::percent, tag::length_dimension::height) const {
	cout << "Converting " << number << "% of height" << endl;
	return number;
}

length_type LengthFactory::create_length(number_type number, tag::length_units::percent, tag::length_dimension::not_width_nor_height) const {
	cout << "Converting " << number << "% of unknown" << endl;
	return number;
}

length_type LengthFactory::length_to_user_coordinate(number_type number, tag::length_dimension::width) const {
	return number;
}

length_type LengthFactory::length_to_user_coordinate(number_type number, tag::length_dimension::height) const {
	return number;
}
