#include "enemy.h"

using namespace godot;

void Enemy::_register_methods() {
    register_method("_process", &Enemy::_process);
    register_method("_ready", &Enemy::_ready);
    register_method("set_target", &Enemy::set_target);
    register_method("_on_body_entered", &Enemy::_on_body_entered);
    register_method("set_hit", &Enemy::set_hit);
    register_method("get_distance", &Enemy::get_distance);
}

Enemy::Enemy() {
}

Enemy::~Enemy() {
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
}

int Enemy::get_distance(int target_x, int target_z, int cur_x, int cur_z) {
    return pow((target_x - cur_x), 2) + pow((target_z - cur_z), 2);
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

void Enemy::_on_body_entered(int body_id, Node *body, int body_shape, int area_shape) {
    if (body->get_parent()->get("place") > get_parent()->get("place")) {
        time_hit = time(NULL);
    } else {
        body->call("set_hit");
    }
}

void Enemy::set_hit() {
    time_hit = time(NULL);
}

void Enemy::_process(float delta) {
    if (time(NULL) - 1.5 > time_hit) {
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
        if (target_rotate < this->get_rotation().y) {
            rotate_y(-0.2);
        } else if (target_rotate > this->get_rotation().y) {
            rotate_y(0.2);
        }
        move_and_slide((move.operator*(3)));
    }
    else {
        rotate_y(.3);
    }
}