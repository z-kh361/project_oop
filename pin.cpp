#include "pin.h"

Pin::Pin(const std::string& name, const vector2d& position)
    : name(name),
      position(position),
      state(logicstate::floating),
      sensitivity_radius(5.0f),
      highlighted(false) {}

bool Pin::is_mouse_over(const vector2d& mouse_pos) const {
    return position.distance_to(mouse_pos) <= sensitivity_radius;
}

std::string Pin::get_name() const {
    return name;
}

void Pin::set_name(const std::string& new_name) {
    name = new_name;
}

vector2d Pin::get_position() const {
    return position;
}

void Pin::set_position(const vector2d& new_position) {
    position = new_position;
}

logicstate Pin::get_state() const {
    return state;
}

void Pin::set_state(logicstate new_state) {
    state = new_state;
}

float Pin::get_sensitivity_radius() const {
    return sensitivity_radius;
}

void Pin::set_sensitivity_radius(float new_radius) {
    sensitivity_radius = new_radius;
}

bool Pin::is_highlighted() const {
    return highlighted;
}

void Pin::set_highlighted(bool value) {
    highlighted = value;
}
