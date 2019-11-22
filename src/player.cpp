#include "player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
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
}

void Player::_process(float delta) {
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