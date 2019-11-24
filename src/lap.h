#ifndef LAP_H
#define LAP_H

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Label.hpp>
#include <String.hpp>

namespace godot {

class Lap : public Spatial {
    GODOT_CLASS(Lap, Spatial)

private:
    int lap;

public:
    static void _register_methods();

    Lap();
    ~Lap();

    void _init();
    void _ready();
	void _on_body_entered(int body_id, Node *body, int body_shape, int area_shape);
};

}

#endif