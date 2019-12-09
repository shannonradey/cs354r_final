#include "enemy2.h"

using namespace godot;

void Enemy2::_register_methods() {
	register_method("_on_body_entered", &Enemy2::_on_body_entered);
	register_method("_ready", &Enemy2::_ready);
	register_method("_process", &Enemy2::_process);
	register_method("set_target", &Enemy2::set_target);
	register_method("hit", &Enemy2::hit);
}

Enemy2::Enemy2() {
}

Enemy2::~Enemy2() {
}

void Enemy2::_ready() {
	Node *node = get_node("Area2");
	node->connect("body_shape_entered", this, "_on_body_entered");
	waypoints = get_parent()->get_node("Path2")->get_children();
	cur_waypoint = 0;
	target = Vector3();
	set_target();
	gravity = 9.8;
	node = get_node("Area");
	node->connect("body_shape_entered", this, "hit");
}

void Enemy2::set_target() {
	cur_waypoint = !cur_waypoint;
	Vector3 new_target = ((Spatial *)waypoints[cur_waypoint])->get_global_transform().origin;
	target.x = round(int(new_target.x));
	target.z = round(int(new_target.z));
}

void Enemy2::hit(int body_id, Node *body, int body_shape, int area_shape) { 
	body->call("hit_slow");
}

void Enemy2::_on_body_entered(int body_id, Node *body, int body_shape, int area_shape) {
	Vector3 new_target = ((Spatial *)body)->get_global_transform().origin;
	target.x = round(int(new_target.x));
	target.z = round(int(new_target.z));

}

void Enemy2::_process(float delta) { 
	Vector3 move = Vector3();
	Vector3 cur_pos = get_global_transform().origin;
	if (int(round(cur_pos.x)) == target.x && int(round(cur_pos.z)) == target.z) {
	    set_target();
	}
	if (target.x < cur_pos.x) {
	    move.x += -1;
	}
	else if (target.x > cur_pos.x) {
	    move.x += 1;
	}
	if (target.z > cur_pos.z) {
	    move.z += 1;
	}
	else if (target.z < cur_pos.z) {
	    move.z += -1;
	}

	translate((move.operator*(.08)));
}

void Enemy2::_init() {
}
