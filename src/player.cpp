#include "player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("box_grab", &Player::box_grab);
    register_method("hit_slow", &Player::hit_slow);
    register_method("set_hit", &Player::set_hit);
}

Player::Player() {
}

Player::~Player() {
}

void Player::box_grab() { 
    int random = rand()%2+1;
    if (random == 1){
        Node *area = get_node("Ball");
        ((Area *)area)->set_visible(true);
        area->call("set_target");
    }
    else{
        speed = 23;
        box_time = time(NULL);
    }
}

void Player::_init() {
    input = Input::get_singleton();
}

void Player::set_hit() {
    time_hit = time(NULL);
}

void Player::_ready() {
    set_name("player");
    time_hit = time(NULL) - 2;
    speed = 13;

    gravity = 9.8;
  
}

void Player::hit_slow() {
    speed = 2;
    box_time = time(NULL);
}

void Player::_process(float delta) {
    if (time(NULL) - 2.5 > box_time) {

        speed = 13;

    }
    if (time(NULL) - 1.5 > time_hit) {
        ((Spatial *)get_node("car"))->set_rotation_degrees(Vector3(0, 90, 0));
        ((Spatial *)get_node("player"))->set_rotation_degrees(Vector3(0, 90, 0));
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
        velocity.y -= gravity * delta;
        move_and_slide(velocity * (speed));
    }
    else {
        ((Spatial *)get_node("car"))->rotate_y(.4);
        ((Spatial *)get_node("player"))->rotate_y(.4);
    }



}