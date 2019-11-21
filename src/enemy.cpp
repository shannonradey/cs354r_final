#include "enemy.h"

using namespace godot;

void Enemy::_register_methods() {
    register_method("_process", &Enemy::_process);
    register_method("_ready", &Enemy::_ready);
    register_method("set_target", &Enemy::set_target);
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
}

void Enemy::set_target() {
    Vector3 new_target = ((Spatial *)waypoints[cur_waypoint])->get_global_transform().origin;
    target.x = round(int(new_target.x));
    target.z = round(int(new_target.z));
}

void Enemy::_process(float delta) {
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
    if (target.y > cur_pos.y) {
        move.y += 1;
    }
    else if (target.y < cur_pos.y) {
        move.y += -1;
    }
    move.x += .0001;
    move.z += .0001;
    move_and_slide((move.operator*(6)));
}