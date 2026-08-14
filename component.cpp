#include "component.h"

Component::Component(const std::string& name,
                     const std::string& type,
                     const vector2d& position)
    : name(name),
      type(type),
      position(position),
      selected(false),
      rotation(0),
      flip_h(false),
      flip_v(false) {}

void Component::update_pins() {
    // class haye badi pin ha ro inja update mikonan
}

std::string Component::get_display_name() const {
    return name;
}

std::vector<std::string> Component::get_property_names() const {
    return {"name", "type", "x", "y", "rotation", "flip_h", "flip_v"};
}

std::string Component::get_property(const std::string& key) const {
    if (key == "name") {
        return name;
    }
    if (key == "type") {
        return type;
    }
    if (key == "x") {
        return std::to_string(position.x);
    }
    if (key == "y") {
        return std::to_string(position.y);
    }
    if (key == "rotation") {
        return std::to_string(rotation);
    }
    if (key == "flip_h") {
        return flip_h ? "true" : "false";
    }
    if (key == "flip_v") {
        return flip_v ? "true" : "false";
    }

    return "";
}

void Component::set_property(const std::string& key, const std::string& value) {
    if (key == "name") {
        name = value;
    } else if (key == "type") {
        type = value;
    } else if (key == "x") {
        position.x = std::stof(value);
    } else if (key == "y") {
        position.y = std::stof(value);
    } else if (key == "rotation") {
        set_rotation(std::stoi(value));
    } else if (key == "flip_h") {
        flip_h = (value == "true" || value == "1");
    } else if (key == "flip_v") {
        flip_v = (value == "true" || value == "1");
    }
}

void Component::select() {
    selected = true;
}

void Component::deselect() {
    selected = false;
}

std::string Component::get_name() const {
    return name;
}

void Component::set_name(const std::string& new_name) {
    name = new_name;
}

std::string Component::get_type() const {
    return type;
}

void Component::set_type(const std::string& new_type) {
    type = new_type;
}

vector2d Component::get_position() const {
    return position;
}

void Component::set_position(const vector2d& new_position) {
    position = new_position;
    update_pins();
}

std::vector<Pin>& Component::get_pins() {
    return pins;
}

const std::vector<Pin>& Component::get_pins() const {
    return pins;
}

bool Component::is_selected() const {
    return selected;
}

int Component::get_rotation() const {
    return rotation;
}

void Component::set_rotation(int new_rotation) {
    rotation = ((new_rotation % 360) + 360) % 360;
    update_pins();
}

bool Component::is_flip_h() const {
    return flip_h;
}

void Component::set_flip_h(bool value) {
    flip_h = value;
    update_pins();
}

bool Component::is_flip_v() const {
    return flip_v;
}

void Component::set_flip_v(bool value) {
    flip_v = value;
    update_pins();
}
