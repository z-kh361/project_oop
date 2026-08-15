#include "resistor.h"

Resistor::Resistor(const std::string& name, const vector2d& position)
    : Component(name, "Resistor", position),
      resistance_(1000.0f) {
    pins.emplace_back("Pin1", position);
    pins.emplace_back("Pin2", position);

    update_pins();
}

void Resistor::update_pins() {
    const float pin_distance = 20.0f;
    vector2d first_offset(-pin_distance, 0.0f);
    vector2d second_offset(pin_distance, 0.0f);

    // Rotate offsets. In screen مختصات y به سمت پایین زیاد میشه.
    if (rotation == 90) {
        first_offset = vector2d(0.0f, -pin_distance);
        second_offset = vector2d(0.0f, pin_distance);
    } else if (rotation == 180) {
        first_offset = vector2d(pin_distance, 0.0f);
        second_offset = vector2d(-pin_distance, 0.0f);
    } else if (rotation == 270) {
        first_offset = vector2d(0.0f, pin_distance);
        second_offset = vector2d(0.0f, -pin_distance);
    }

    pins[0].set_position(vector2d(position.x + first_offset.x,
                                  position.y + first_offset.y));
    pins[1].set_position(vector2d(position.x + second_offset.x,
                                  position.y + second_offset.y));
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
