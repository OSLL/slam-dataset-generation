#include "world/path.h"
#include <iostream>
#include <string>

using std::ostream;
using std::endl;
using std::string;

Path::Path(const Vec & start_point) :
	_start(start_point),
	_end_ptr(&_start)
{ }

Path::~Path() {
	// In this case, RAII isn't really being obeyed, because dynamic allocation happens in ParsingContext, not in Path
	for (Edge * e : edges) {
		delete e;
	}
}

// Getters
const Vec & Path::start() { return _start; }
const string & Path::id() { return _id; }
const Vec & Path::end() { return *_end_ptr; }

// Setters
void Path::set_id(const string & id_value) { _id = id_value; }

void Path::add_edge(Edge * e) {
	edges.push_back(e);
	_end_ptr = &e->end;
}

void Path::print(ostream & o, int tabs) const {
	// Print the correct number of tabs
	for (int i = 0; i < tabs; i++) {
		o << '\t';
	}

	// Print data
	o << "Path: " << _id << endl;
	
	o << edges.size() << endl;

	for (Edge * e : edges) {
		e->print(o, tabs + 1);
	}
}

ostream & operator<<(ostream & o, const Path & path) {
	path.print();
}
