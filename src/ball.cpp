#include "ball.h"

using namespace godot;

void Ball::_register_methods() {
    register_method("_process", &Ball::_process);
    register_method("_ready", &Ball::_ready);
    register_method("set_target", &Ball::set_target);

}

Ball::Ball() {
}

Ball::~Ball() {
}



void Ball::_init() {
    velocity = 5;
    gravity = 9.8;

}

void Ball::_ready() {
    closest_target = get_parent();
    set_name("Ball");
 
}


void Ball::set_target() {
    Node *enemy1 = get_parent()->get_parent()->get_parent()->get_node("Enemy1");
    Node *enemy2 = get_parent()->get_parent()->get_parent()->get_node("Enemy2");
    Node *enemy3 = get_parent()->get_parent()->get_parent()->get_node("Enemy3");
    Node *enemy4 = get_parent()->get_parent()->get_parent()->get_node("Enemy4");
    Node *player = get_parent()->get_parent()->get_parent()->get_node("player");

    Vector3 enemy_coord = ((Spatial *)enemy1->get_child(0))->get_global_transform().origin;
    closest_target = enemy1->get_child(0);


    Vector3 cur_pos = get_global_transform().origin;
    real_t distance = enemy_coord.distance_to(cur_pos);

    Vector3 new_target = ((Spatial *)enemy2->get_child(0))->get_global_transform().origin;
    real_t new_dist = new_target.distance_to(cur_pos);
    if (new_dist < distance && enemy2->get_child(0) != get_parent()) {
        enemy_coord= new_target;
        distance = new_dist;
        closest_target = enemy2->get_child(0);
    }

    new_target = ((Spatial *)enemy3->get_child(0))->get_global_transform().origin;
    new_dist = new_target.distance_to(cur_pos);
    if (new_dist < distance && enemy3->get_child(0) != get_parent()) {
        enemy_coord = new_target;
        distance = new_dist;
        closest_target = enemy3->get_child(0);
    }

    new_target = ((Spatial *)enemy4->get_child(0))->get_global_transform().origin;
    new_dist = new_target.distance_to(cur_pos);
    if (new_dist < distance && enemy4->get_child(0) != get_parent()) {
        enemy_coord = new_target;
        distance = new_dist;
        closest_target = enemy4->get_child(0);
    }

    new_target = ((Spatial *)player->get_child(0))->get_global_transform().origin;
    new_dist = new_target.distance_to(cur_pos);
    if (new_dist < distance && player->get_child(0) != get_parent()) {
        enemy_coord = new_target;
        distance = new_dist;
        closest_target = player->get_child(0);
    }
}




          

void Ball::_process(float delta) {
    Vector3 move = Vector3();
    Vector3 cur_pos = get_global_transform().origin;
    target = ((Spatial *)closest_target)->get_global_transform().origin;

    if (int(round(cur_pos.x)) == int(round(target.x)) && int(round(cur_pos.z)) == int(round(target.z))) {
        set_visible(false);
        if (closest_target != get_parent()) {
            closest_target->call("set_hit");
            closest_target = get_parent();
        }
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
    
    global_translate((move.operator*(velocity) * delta));
        
}