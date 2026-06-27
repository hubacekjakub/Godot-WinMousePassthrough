#include "win32_passthrough.h"
#include <godot_cpp/classes/display_server.hpp>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace godot;

Win32Passthrough *Win32Passthrough::singleton = nullptr;

Win32Passthrough *Win32Passthrough::get_singleton() {
    return singleton;
}

Win32Passthrough::Win32Passthrough() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

Win32Passthrough::~Win32Passthrough() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void Win32Passthrough::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_passthrough", "window_id", "enabled"),
        &Win32Passthrough::set_passthrough);
}

void Win32Passthrough::set_passthrough(int64_t window_id, bool enabled) {
#ifdef _WIN32
    int64_t hwnd_int = DisplayServer::get_singleton()->window_get_native_handle(
        DisplayServer::WINDOW_HANDLE, (int)window_id);
    HWND hwnd = (HWND)(intptr_t)hwnd_int;
    if (!hwnd) return;

    LONG_PTR ex = GetWindowLongPtr(hwnd, GWL_EXSTYLE);
    if (enabled)
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, ex | WS_EX_LAYERED | WS_EX_TRANSPARENT);
    else
        SetWindowLongPtr(hwnd, GWL_EXSTYLE, ex & ~WS_EX_TRANSPARENT);

    SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
        SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
#endif
}
