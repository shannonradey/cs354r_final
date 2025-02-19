#include "lap.h"

using namespace godot;

void Lap::_register_methods() {
	register_method("_on_body_entered", &Lap::_on_body_entered);
	register_method("_ready", &Lap::_ready);
}

Lap::Lap() {
}

Lap::~Lap() {
}

void Lap::_ready() {
	Node *node = get_child(0)->get_node("Area");
	node->connect("body_shape_entered", this, "_on_body_entered");
	
}

void Lap::_on_body_entered(int body_id, Node *body, int body_shape, int area_shape) {
	int cur_lap = lap;
	if (body->get_parent()->get_name() == "player") {
		if (cur_lap == 3){
			Node *node = body->get_parent()->get_node("Gui")->get_node("Finished");
			((CanvasItem *)node)->set_visible(true);
			String place = ((Label *)body->get_parent()->
				get_node("Gui")->get_node("HBoxContainer")->
				get_node("NinePatchRect")->get_node("Label"))->get_text();
			((Label *)node->get_node("Place"))->set_text(place);
			if (place == "1") { 
				((Label *)node->get_node("St"))->set_text("st");
			} else if (place == "2") {
				((Label *)node->get_node("St"))->set_text("nd");
			} else if (place == "3") {
				((Label *)node->get_node("St"))->set_text("rd");
			} else {
				((Label *)node->get_node("St"))->set_text("th");
			}
		}
		else{
			int cur_lap = lap + 1;
			Node *node = body->get_parent()->get_node("Gui")->get_node("HBoxContainer")->
				get_node("Lap")->get_node("Label");
			((Label *)node)->set_text(String::num(cur_lap));
			lap = cur_lap;
		}
	}
}

void Lap::_init() {
	lap = 0;
}
