#include "magiccube.h"

using namespace godot;

void MagicCube::_register_methods() {
	register_method("_on_body_entered", &MagicCube::_on_body_entered);
	register_method("_ready", &MagicCube::_ready);
	register_method("_process", &MagicCube::_process);
}

MagicCube::MagicCube() {
}

MagicCube::~MagicCube() {
}

void MagicCube::_ready() {
	this->connect("body_shape_entered", this, "_on_body_entered");
	get_parent()->set_name("cube");
	set_name("cube");
	
}

void MagicCube::_on_body_entered(int body_id, Node *body, int body_shape, int area_shape) {
	if (is_visible()) {
		set_visible(false);
		set_name("not_cube");
		time_hit = time(NULL);
		body->call("box_grab");
	}
}

void MagicCube::_process(float delta) {
	rotate_y(.05);
	rotate_x(-.05);
	rotate_z(.05);
	if (!is_visible()) {
		if (time(NULL) - 10 > time_hit) {
			set_name("cube");
			set_visible(true);
		}
	}
}

void MagicCube::_init() {
}
