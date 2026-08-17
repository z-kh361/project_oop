#include "Ground.h"

Ground::Ground(const std::string& name, const vector2d& position)
    : Component(name, "Ground", position),
      is_connected_(true) {
    pins.emplace_back("GND", position);
    update_pins();
}

void Ground::update_pins() {
    pins[0].set_position(position);
    pins[0].set_state(logicstate::low);
}

std::vector<std::pair<std::string, std::string>> Ground::get_properties() const {
    return {
        {"name", name}
    };
}

logicstate Ground::get_pin_state(int index) const {
    (void)index;
    return is_connected_ ? logicstate::low : logicstate::floating;
}
