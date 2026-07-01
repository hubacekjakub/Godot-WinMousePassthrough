# Windows Mouse Passthrough

A Godot 4 GDExtension that makes mouse clicks pass through a window on Windows, using `WS_EX_LAYERED | WS_EX_TRANSPARENT` Win32 flags. The window itself is unaffected — it can stay fully opaque, or use whatever visual transparency your scene already has — only mouse input is let through to whatever is underneath.

Built for desktop overlay / widget apps where the Godot window sits on top of the desktop but must never intercept mouse input.

**No .NET required** — pure C++ GDExtension, works with any Godot 4.3+ project.

## Platform support

| Platform | Status |
|----------|--------|
| Windows  | Full support |
| Linux / macOS | No-op (extension not loaded; use Godot's built-in transparency if needed) |

## Installation

1. Copy the `addons/windows_mouse_passthrough/` folder into your project's `addons/` directory.
2. Open **Project → Project Settings → Plugins** and enable **Windows Mouse Passthrough**.

## Usage

```gdscript
func _ready() -> void:
    if Engine.has_singleton("MousePassthrough"):
        MousePassthrough.set_passthrough(get_window().get_window_id(), true)
```

### API

```
MousePassthrough.set_passthrough(window_id: int, enabled: bool) -> void
```

- `window_id` — Godot window ID (`get_window().get_window_id()` for the main window)
- `enabled` — `true` to enable passthrough, `false` to restore normal mouse input

The `Engine.has_singleton` guard is recommended so the same script runs unchanged on Linux and macOS.

## Why this exists

Godot's built-in `DisplayServer.window_set_mouse_passthrough(polygon)` defines a polygonal hit region within a single Godot window — it cannot make clicks pass through to other applications underneath. There is no Godot API for Win32 extended window styles.

This extension calls `SetWindowLongPtr` with `WS_EX_LAYERED | WS_EX_TRANSPARENT` directly on the window's HWND. Both flags must be set together — `WS_EX_TRANSPARENT` alone (0x20) is not sufficient; the combination (0x80020) is required.

Note that `WS_EX_LAYERED` is what makes click-through possible on Windows, but it does **not** make the window visually transparent — that's a separate concern handled by Godot's own window transparency settings (`ProjectSettings` → `display/window/per_pixel_transparency`) or your scene's background. A fully opaque window can be just as click-through as a see-through one.

## Example

Clone this repository and open the root folder as a Godot 4.3+ project. The example scene (`example/example.tscn`) activates passthrough for 5 seconds with a live countdown, then restores normal input automatically.

## Building from source

Requires CMake 3.22+, MSVC (Visual Studio 2022), and Ninja.

```bash
git submodule update --init --recursive
cmake -B gdextension/build/release -S gdextension -G Ninja -DGODOT_TARGET=template_release
cmake --build gdextension/build/release
```

Output DLLs are written to `addons/windows_mouse_passthrough/bin/`. The pre-built DLLs committed to this repo were built against godot-cpp pinned to Godot 4.6-stable.

## License

MIT — see [LICENSE](LICENSE)
