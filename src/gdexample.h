#ifndef GDEXAMPLE_H
#define GDEXAMPLE_H

#include <Godot.hpp>
#include <Spatial.hpp>
#include <Label.hpp>
#include <String.hpp>

namespace godot {

class GDExample : public Spatial {
    GODOT_CLASS(GDExample, Spatial)

private:
    int place;

public:
    static void _register_methods();

    GDExample();
    ~GDExample();

    void _init();
    void _ready();
    void set_place(int x);
	void _on_body_entered(int body_id, Node *body, int body_shape, int area_shape);
};

}

#endif