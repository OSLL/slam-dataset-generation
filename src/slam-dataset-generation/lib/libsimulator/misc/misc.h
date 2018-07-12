#ifndef MISC_H
#define MISC_H


/* This file is just for a bunch of useful functions that dont' really deserve their own translation unit */

#include <string>
#include <set>
#include <typeinfo>
#include <iostream>

// Demangle g++ type information
std::string demangle(const char * name);
template <class T>
std::string type(const T & t) {
	return demangle(typeid(t).name());
}

// Print out a set
template <typename T>
std::ostream & operator<<(std::ostream & o, std::set<T> s) {
	o << "{";

	// If set is not empty, print contents
	if (!s.empty()) {

		// Padding space
		o << " ";

		// Print out first element and advance iterator
		typename std::set<T>::iterator i = s.begin();
		o << *i;
		i++;

		// If there are additional elements, print them with commas seperating previous values
		for (; i != s.end(); i++) {
			o << ", " << *i;
		}

		// Padding space
		o << " ";
	}

	o << "}";

	return o;
}

// Get signum of a value
template <typename T>
int sign(T value) {
	return (T(0) < value) - (value < T(0));
}

double generate_random_number(const double & min, const double & max);

#endif
