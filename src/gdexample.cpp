#include "gdexample.h"

using namespace godot;

void GDExample::_register_methods() {
	register_property<GDExample, int>("place", &GDExample::place, 0);
	register_method("_on_body_entered", &GDExample::_on_body_entered);
	register_method("_ready", &GDExample::_ready);
	register_method("set_place", &GDExample::set_place);
}

GDExample::GDExample() {
}

GDExample::~GDExample() {
    // add your cleanup here
}

void GDExample::_ready() {
	Node *node = get_child(0)->get_node("FrontArea");
	node->connect("body_shape_entered", this, "_on_body_entered");
	if (get_child(0)->get_name() == "player") {
		node = get_node("Gui")->get_node("HBoxContainer")->
			get_node("NinePatchRect")->get_node("Label");
		((Label *)node)->set_text(String::num(place));
	}
}

void GDExample::_on_body_entered(int body_id, Node *body, int body_shape, int area_shape) {
	int body_place = body->get_parent()->get("place");
	if (body_place > place) {
		body->get_parent()->call("set_place", place);
		place = body_place;
		this->set_place(place);
	}
}

void GDExample::set_place(int x) {
	place = x;
	if (get_child(0)->get_name() == "player") {
		Node *node = get_node("Gui")->get_node("HBoxContainer")->
			get_node("NinePatchRect")->get_node("Label");
		((Label *)node)->set_text(String::num(place));
	}
}

void GDExample::_init() {

}
