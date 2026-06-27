#pragma once
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class Win32Passthrough : public Object {
    GDCLASS(Win32Passthrough, Object)

    static Win32Passthrough *singleton;

public:
    static Win32Passthrough *get_singleton();

    Win32Passthrough();
    ~Win32Passthrough();

    void set_passthrough(int64_t window_id, bool enabled);

protected:
    static void _bind_methods();
};
