#include "gdexample.h"

using namespace godot;

void GDExample::_register_methods() {
	register_property<GDExample, int>("place", &GDExample::place, 1);
}

GDExample::GDExample() {
}

GDExample::~GDExample() {
    // add your cleanup here
}

void GDExample::_init() {
}
