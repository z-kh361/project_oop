#include "resistor.h"

Resistor::Resistor(const std::string& name, const vector2d& position)
    : Component(name, "Resistor", position),
      resistance_(1000.0f) {
    pins.emplace_back("Pin1", position);
    pins.emplace_back("Pin2", position);

    update_pins();
}

void Resistor::update_pins() {
    pins[0].set_position(vector2d(position.x - 15.0f, position.y));
    pins[1].set_position(vector2d(position.x + 15.0f, position.y));
}

std::string Resistor::get_display_name() const {
    return name;
}

float Resistor::get_resistance() const {
    return resistance_;
}

void Resistor::set_resistance(float resistance) {
    resistance_ = resistance;
}
