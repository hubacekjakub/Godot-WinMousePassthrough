#pragma once
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class MousePassthrough : public Object {
    GDCLASS(MousePassthrough, Object)

    static MousePassthrough *singleton;

public:
    static MousePassthrough *get_singleton();

    MousePassthrough();
    ~MousePassthrough();

    void set_passthrough(int64_t window_id, bool enabled);

protected:
    static void _bind_methods();
};
