#include "enemy.h"

using namespace godot;

void Enemy::_register_methods() {
    register_method("_process", &Enemy::_process);
    register_method("_ready", &Enemy::_ready);
    register_method("set_target", &Enemy::set_target);
    register_method("_on_body_entered", &Enemy::_on_body_entered);
    register_method("check_for_box", &Enemy::check_for_box);
    register_method("set_hit", &Enemy::set_hit);
    register_method("box_grab", &Enemy::box_grab);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
}

void Enemy::box_grab() {
    Godot::print("box_grab");
    velocity = 10;
    speed = time(NULL);
}

void Enemy::_init() {

}

void Enemy::_ready() {
    waypoints = get_parent()->get_parent()->get_node("Path")->get_children();
    num_waypoints = waypoints.size();
    cur_waypoint = 0;
    set_target();
    set_name("enemy");
    Node *node = get_node("Area");
    node->connect("body_shape_entered", this, "_on_body_entered");
    time_hit = time(NULL) - 5;
    node = get_node("Area2");
    node->connect("body_shape_entered", this, "check_for_box");
    velocity = 3;
}


void Enemy::set_target() {
    Array spatials = ((Spatial *)waypoints[cur_waypoint])->get_children();
    Vector3 closest_target = ((Spatial *)spatials[0])->get_global_transform().origin;
    Node *nearest_node = spatials[0];
    Vector3 cur_pos = get_global_transform().origin;
    real_t distance = closest_target.distance_to(cur_pos);
    int len = spatials.size();
    for (int i = 0; i < len; i++) {
        Spatial *s = spatials[i];
        Vector3 new_target = ((Spatial *)spatials[i])->get_global_transform().origin;
        real_t new_dist = new_target.distance_to(cur_pos);
        if (new_dist < distance) {
            closest_target = new_target;
            distance = new_dist;
        }
    }
    target.x = round(int(closest_target.x));
    target.z = round(int(closest_target.z));
    target_rotate = ((Spatial *)waypoints[cur_waypoint])->get_rotation().y;
}

void Enemy::check_for_box(int body_id, Node *body, int body_shape, int area_shape) {
    Godot::print(body->get_name());
    if (body->get_name() == "cube" && ((CanvasItem *)body)->is_visible()) {
        Godot::print("found box");
        Vector3 closest_target = ((Spatial *)body)->get_global_transform().origin;
        target.x = round(int(closest_target.x));
        target.y = round(int(closest_target.y));
    }
}

void Enemy::_on_body_entered(int body_id, Node *body, int body_shape, int area_shape) {
    // if (body->get_parent()->get("place") > get_parent()->get("place"))
    //     time_hit = time(NULL);
    // else
    //     body->call("set_hit");
}
          
void Enemy::set_hit() {
    time_hit = time(NULL);
}

void Enemy::_process(float delta) {
    if (time(NULL) - 2.5 > speed) {
        velocity = 3;
    }
    if (time(NULL) - 0.5 > time_hit) {
        if (target_rotate < this->get_rotation().y) {
            rotate_y(-0.05);
        } else if (target_rotate > this->get_rotation().y) {
            rotate_y(0.05);
        }
        Vector3 move = Vector3();
        Vector3 cur_pos = get_global_transform().origin;
        if (int(round(cur_pos.x)) == target.x && int(round(cur_pos.z)) == target.z) {
            cur_waypoint++;
            if (cur_waypoint == num_waypoints)
                cur_waypoint = 0;
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
        
        move_and_slide((move.operator*(velocity)));
    }
    else {
        rotate_y(.3);
    }
}