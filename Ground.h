#ifndef GROUND_H
#define GROUND_H

#include "component.h"

class Ground : public Component {
private:
    bool is_connected_;

public:
    // ground jadid misaze
    Ground(const std::string& name, const vector2d& position);

    // pin ha ro update mikone
    void update_pins() override;

    // property ha ro ba meghdar namayesh mide
    std::vector<std::pair<std::string, std::string>> get_properties() const override;

    // state pin ro mide
    logicstate get_pin_state(int index) const override;
};

#endif
