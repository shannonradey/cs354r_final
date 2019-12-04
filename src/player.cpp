#include "player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("set_hit", &Player::set_hit);
}

Player::Player() {
}

Player::~Player() {
}

void Player::_init() {
    input = Input::get_singleton();
}

void Player::_ready() {
    set_name("player");
    time_hit = time(NULL) - 2;
}

void Player::set_hit() {
    time_hit = time(NULL);
}

void Player::_process(float delta) {
    if (time(NULL) - 1.5 > time_hit) {
    	Vector3 cur;
    	Vector3 velocity = Vector3(0, 0, 0);
    	if (input->is_action_pressed("ui_down")) {
            cur = get_global_transform().basis.z; 
            cur.y = 0;
            velocity += cur.rotated(Vector3(0, 1, 0), -M_PI/2);
        }
        if (input->is_action_pressed("ui_up")) {
            cur = get_global_transform().basis.z;
            cur.y = 0;
            velocity += cur.rotated(Vector3(0, 1, 0), M_PI/2);
        }
        if (input->is_action_pressed("ui_left")) {
            rotate_y(0.02);
        }
        if (input->is_action_pressed("ui_right")) {
            rotate_y(-0.02);
        }
        move_and_slide(velocity * 10);
    }
    else {
        rotate_y(.3);
    }
}