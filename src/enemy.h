#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <KinematicCollision.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>
#include <CanvasItem.hpp>

namespace godot {

class Enemy : public KinematicBody {
    GODOT_CLASS(Enemy, KinematicBody);

private:
	Array waypoints;
	int num_waypoints;
	Vector3 target;
	int cur_waypoint;
    time_t time_hit;
    int target_rotate;
    double velocity;
    time_t speed;
    double gravity;

public:
    static void _register_methods();

    Enemy();
    ~Enemy();

    void _init();
    void box_grab();
    void _process(float delta);
    void set_target();
    void set_hit();
    void _ready();
    void _on_body_entered(int body_id, Node *body, int body_shape, int area_shape);
    void check_for_box(int body_id, Node *body, int body_shape, int area_shape);
};

}

#endif