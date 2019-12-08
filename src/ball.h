#ifndef BALL_H
#define BALL_H

#include <Godot.hpp>
#include <Area.hpp>

namespace godot {

class Ball : public Area {
    GODOT_CLASS(Ball, Area)

private:
	Vector3 target;
	double velocity;
    double gravity;
    Node* closest_target;

public:
    static void _register_methods();

    Ball();
    ~Ball();

    void _init();
    void _ready();
    void _process(float delta);
    void set_target();
};

}

#endif