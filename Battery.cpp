#include "Battery.h"

Battery::Battery(const std::string& name, const vector2d& position)
    : Component(name, "Battery", position),
      voltage_(9.0f) {
    pins.emplace_back("Positive", position);
    pins.emplace_back("Negative", position);

    pins[0].set_state(logicstate::high);
    pins[1].set_state(logicstate::low);
    update_pins();
}

void Battery::update_pins() {
    pins[0].set_position(vector2d(position.x + 15.0f, position.y));
    pins[1].set_position(vector2d(position.x - 15.0f, position.y));

    pins[0].set_state(logicstate::high);
    pins[1].set_state(logicstate::low);
}

std::vector<std::pair<std::string, std::string>> Battery::get_properties() const {
    return {
        {"name", name},
        {"voltage", std::to_string(voltage_)}
    };
}

void Battery::set_property(const std::string& key, const std::string& value) {
    if (key == "voltage" || key == "Voltage") {
        voltage_ = std::stof(value);
        return;
    }

    Component::set_property(key == "Name" ? "name" : key, value);
}

float Battery::get_voltage() const {
    return voltage_;
}
