# Windows Mouse Passthrough

Makes mouse clicks pass through a Godot 4 window on Windows, using `WS_EX_LAYERED | WS_EX_TRANSPARENT` Win32 flags. No .NET required — pure C++ GDExtension.

The window's visuals are unaffected — it can be fully opaque or partially transparent, that's independent of this addon. This only controls whether clicks reach the window or fall through to whatever is behind it.

## Installation

1. Copy the `windows_mouse_passthrough/` folder into your project's `addons/` directory.
2. Go to **Project → Project Settings → Plugins** and enable **Windows Mouse Passthrough**.

## Usage

```gdscript
func _ready() -> void:
    if Engine.has_singleton("MousePassthrough"):
        Engine.get_singleton("MousePassthrough").set_passthrough(get_window().get_window_id(), true)
```

The `Engine.has_singleton` guard keeps the script cross-platform safe — the extension is a no-op on Linux and macOS.

## API

```
MousePassthrough.set_passthrough(window_id: int, enabled: bool) -> void
```

- `window_id` — use `get_window().get_window_id()` for the main window
- `enabled` — `true` to enable passthrough, `false` to restore normal input

## Requirements

- Godot 4.3+
- Windows only
