#include "register_types.h"
#include "mouse_passthrough.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static MousePassthrough *passthrough_singleton = nullptr;

void initialize_mouse_passthrough_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    GDREGISTER_CLASS(MousePassthrough);
    passthrough_singleton = memnew(MousePassthrough);
    Engine::get_singleton()->register_singleton("MousePassthrough", passthrough_singleton);
}

void uninitialize_mouse_passthrough_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    Engine::get_singleton()->unregister_singleton("MousePassthrough");
    memdelete(passthrough_singleton);
    passthrough_singleton = nullptr;
}

extern "C" {
GDExtensionBool GDE_EXPORT mouse_passthrough_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(
        p_get_proc_address, p_library, r_initialization);
    init_obj.register_initializer(initialize_mouse_passthrough_module);
    init_obj.register_terminator(uninitialize_mouse_passthrough_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
    return init_obj.init();
}
}
