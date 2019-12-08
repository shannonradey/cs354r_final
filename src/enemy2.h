#ifndef ENEMY2_H
#define ENEMY2_H

#include <Godot.hpp>
#include <Spatial.hpp>

namespace godot {

class Enemy2 : public Spatial {
    GODOT_CLASS(Enemy2, Spatial)

private:
	Array waypoints;
	Vector3 target;
	int cur_waypoint;
	double gravity;


public:
    static void _register_methods();

    Enemy2();
    ~Enemy2();

    void _init();
    void _ready();
    void set_target();
    void _process(float delta);
    void hit(int body_id, Node *body, int body_shape, int area_shape);
	void _on_body_entered(int body_id, Node *body, int body_shape, int area_shape);
};

}

#endif