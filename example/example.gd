extends Control

const DURATION := 30.0

@onready var status_label: Label = $VBox/StatusLabel
@onready var countdown_label: Label = $VBox/CountdownLabel
@onready var progress_bar: ProgressBar = $VBox/ProgressBar
@onready var button: Button = $VBox/Button
@onready var always_on_top: CheckButton = $VBox/AlwaysOnTop
@onready var timer: Timer = $Timer

var _tween: Tween
var _seconds_left: int = 0


func _ready() -> void:
	timer.timeout.connect(_on_tick)
	button.pressed.connect(_start)
	always_on_top.toggled.connect(_on_always_on_top_toggled)

	if not Engine.has_singleton("MousePassthrough"):
		status_label.text = "Not available (Windows only)"
		button.disabled = true


func _start() -> void:
	Engine.get_singleton("MousePassthrough").set_passthrough(get_window().get_window_id(), true)

	button.disabled = true
	status_label.text = "Clicks are passing through the window!"
	_seconds_left = int(DURATION)
	_update_countdown()

	if _tween:
		_tween.kill()
	_tween = create_tween()
	_tween.tween_property(progress_bar, "value", 0.0, DURATION).set_ease(Tween.EASE_IN)
	_tween.finished.connect(_stop)

	timer.start()


func _on_tick() -> void:
	_seconds_left -= 1
	_update_countdown()
	if _seconds_left <= 0:
		timer.stop()


func _update_countdown() -> void:
	countdown_label.text = "%d" % _seconds_left


func _stop() -> void:
	Engine.get_singleton("MousePassthrough").set_passthrough(get_window().get_window_id(), false)
	timer.stop()
	_reset()


func _on_always_on_top_toggled(enabled: bool) -> void:
	DisplayServer.window_set_flag(DisplayServer.WINDOW_FLAG_ALWAYS_ON_TOP, enabled)


func _reset() -> void:
	button.disabled = false
	status_label.text = "Click to test for 30 seconds"
	countdown_label.text = ""
	progress_bar.value = DURATION
