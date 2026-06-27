extends Control

@onready var status_label: Label = $VBox/Status
@onready var toggle_button: Button = $VBox/Toggle

func _ready() -> void:
	toggle_button.toggled.connect(_on_toggle)
	_update_status(false)

	if not Engine.has_singleton("Win32Passthrough"):
		status_label.text = "Status: Not available (Windows only)"
		toggle_button.disabled = true


func _on_toggle(enabled: bool) -> void:
	if Engine.has_singleton("Win32Passthrough"):
		Engine.get_singleton("Win32Passthrough").set_passthrough(get_window().get_window_id(), enabled)
	_update_status(enabled)


func _update_status(enabled: bool) -> void:
	status_label.text = "Status: " + ("ON — clicks pass through" if enabled else "OFF")
	toggle_button.text = "Disable Passthrough" if enabled else "Enable Passthrough"
