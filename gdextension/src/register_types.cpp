#include "register_types.h"
#include "win32_passthrough.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

static Win32Passthrough *passthrough_singleton = nullptr;

void initialize_win32_passthrough_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    GDREGISTER_CLASS(Win32Passthrough);
    passthrough_singleton = memnew(Win32Passthrough);
    Engine::get_singleton()->register_singleton("Win32Passthrough", passthrough_singleton);
}

void uninitialize_win32_passthrough_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    Engine::get_singleton()->unregister_singleton("Win32Passthrough");
    memdelete(passthrough_singleton);
    passthrough_singleton = nullptr;
}

extern "C" {
GDExtensionBool GDE_EXPORT win32_passthrough_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(
        p_get_proc_address, p_library, r_initialization);
    init_obj.register_initializer(initialize_win32_passthrough_module);
    init_obj.register_terminator(uninitialize_win32_passthrough_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
    return init_obj.init();
}
}
