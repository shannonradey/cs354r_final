#ifndef ENEMY_H
#define ENEMY_H

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <KinematicCollision.hpp>
#include <SceneTree.hpp>
#include <Viewport.hpp>

namespace godot {

class Enemy : public KinematicBody {
    GODOT_CLASS(Enemy, KinematicBody);

private:
	Array waypoints;
	int num_waypoints;
	Vector3 target;
	int cur_waypoint;

public:
    static void _register_methods();

    Enemy();
    ~Enemy();

    void _init();

    void _process(float delta);
    void set_target();
    void _ready();
};

}

#endif