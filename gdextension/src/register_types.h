#pragma once
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_win32_passthrough_module(ModuleInitializationLevel p_level);
void uninitialize_win32_passthrough_module(ModuleInitializationLevel p_level);
