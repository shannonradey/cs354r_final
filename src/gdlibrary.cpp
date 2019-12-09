#include "gdexample.h"
#include "player.h"
#include "enemy.h"
#include "lap.h"
#include "magiccube.h"

#include "ball.h"

#include "enemy2.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
    godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
    godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
    godot::Godot::nativescript_init(handle);

    godot::register_class<godot::GDExample>();
    godot::register_class<godot::Player>();
    godot::register_class<godot::Enemy>();
    godot::register_class<godot::Lap>();
    godot::register_class<godot::MagicCube>();

    godot::register_class<godot::Ball>();

    godot::register_class<godot::Enemy2>();
}