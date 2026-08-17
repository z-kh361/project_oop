#include "Switch.h"

Switch::Switch(const std::string& name, const vector2d& position)
    : Component(name, "Switch", position),
      is_closed_(false) {
    pins.emplace_back("Pin1", position);
    pins.emplace_back("Pin2", position);

    update_pins();
}

void Switch::update_pins() {
    pins[0].set_position(vector2d(position.x - 15.0f, position.y));
    pins[1].set_position(vector2d(position.x + 15.0f, position.y));

    if (!is_closed_) {
        pins[1].set_state(logicstate::floating);
    }
}

std::vector<std::pair<std::string, std::string>> Switch::get_properties() const {
    return {
        {"name", name},
        {"state", is_closed_ ? "Closed" : "Open"}
    };
}

void Switch::set_property(const std::string& key, const std::string& value) {
    if (key == "state" || key == "State") {
        is_closed_ = value == "Closed" || value == "closed" ||
                     value == "1" || value == "true";
        update_pins();
        return;
    }

    Component::set_property(key == "Name" ? "name" : key, value);
}

void Switch::toggle() {
    is_closed_ = !is_closed_;
    update_pins();
}

logicstate Switch::get_pin_state(int index) const {
    if (index < 0 || index >= static_cast<int>(pins.size())) {
        return logicstate::undefined;
    }

    if (!is_closed_ && index == 1) {
        return logicstate::floating;
    }

    return pins[index].get_state();
}

bool Switch::is_closed() const {
    return is_closed_;
}
