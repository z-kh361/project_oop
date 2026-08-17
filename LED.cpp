#include "LED.h"

LED::LED(const std::string& name, const vector2d& position)
    : Component(name, "LED", position),
      color_("Red"),
      is_on_(false) {
    pins.emplace_back("Anode", position);
    pins.emplace_back("Cathode", position);

    update_pins();
}

void LED::update_pins() {
    pins[0].set_position(vector2d(position.x + 15.0f, position.y));
    pins[1].set_position(vector2d(position.x - 15.0f, position.y));
}

std::vector<std::pair<std::string, std::string>> LED::get_properties() const {
    return {
        {"name", name},
        {"color", color_}
    };
}

void LED::set_property(const std::string& key, const std::string& value) {
    if (key == "color" || key == "Color") {
        color_ = value;
        return;
    }

    Component::set_property(key == "Name" ? "name" : key, value);
}

void LED::update_state(logicstate anode_state, logicstate cathode_state) {
    is_on_ = anode_state == logicstate::high &&
             cathode_state == logicstate::low;
}

bool LED::is_on() const {
    return is_on_;
}
