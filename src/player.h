#ifndef PLAYER_H
#define PLAYER_H

#include <Godot.hpp>
#include <KinematicBody.hpp>
#include <KinematicCollision.hpp>
#include <Input.hpp>

namespace godot {

class Player : public KinematicBody {
    GODOT_CLASS(Player, KinematicBody)

private:
	Input *input;
	time_t time_hit;
    double speed;
    time_t box_time;
    double gravity;

public:
    static void _register_methods();

    Player();
    ~Player();

    void _init(); // our initializer called by Godot
    void _ready();
    void hit_slow();
    void _process(float delta);
    void box_grab();
};

}

#endif