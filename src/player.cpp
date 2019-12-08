#include "player.h"

using namespace godot;

void Player::_register_methods() {
    register_method("_process", &Player::_process);
    register_method("_ready", &Player::_ready);
    register_method("box_grab", &Player::box_grab);
    register_method("hit_slow", &Player::hit_slow);
}

Player::Player() {
}

Player::~Player() {
}

void Player::box_grab() { 
    int random = 1;
    Godot::print(String::num(random));
    if (random == 1){
        Node *area = get_node("Ball");
        ((Area *)area)->set_visible(true);
        area->call("set_target");
    }
    else{
        speed = 20;
        box_time = time(NULL);
    }
}

void Player::_init() {
    input = Input::get_singleton();
}

void Player::_ready() {
    set_name("player");
    time_hit = time(NULL) - 2;
    speed = 10;

    gravity = 9.8;
  

    
    
    //Godot::print(enemies[0]->get_name());
}

void Player::hit_slow() {
    speed = 2;
    box_time = time(NULL);
}

void Player::_process(float delta) {
    if (time(NULL) - 2.5 > box_time) {

        speed = 10;

    }
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
        velocity.y -= gravity * delta;
        move_and_slide(velocity * (speed));
    }
    else {
        rotate_y(.3);
    }



}