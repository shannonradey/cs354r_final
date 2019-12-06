#ifndef MAGICCUBE_H
#define MAGICCUBE_H

#include <Godot.hpp>
#include <Area.hpp>

namespace godot {

class MagicCube : public Area {
    GODOT_CLASS(MagicCube, Area)

private:
	time_t time_hit;

public:
    static void _register_methods();

    MagicCube();
    ~MagicCube();

    void _init();
    void _ready();
    void _process(float delta);
	void _on_body_entered(int body_id, Node *body, int body_shape, int area_shape);
};

}

#endif