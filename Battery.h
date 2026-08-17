#ifndef BATTERY_H
#define BATTERY_H

#include "component.h"

class Battery : public Component {
private:
    float voltage_;

public:
    // battery jadid misaze
    Battery(const std::string& name, const vector2d& position);

    // pin ha ro update mikone
    void update_pins() override;

    // property ha ro ba meghdar namayesh mide
    std::vector<std::pair<std::string, std::string>> get_properties() const override;

    // property ro avaz mikone
    void set_property(const std::string& key, const std::string& value) override;

    // voltage ro mide
    float get_voltage() const;
};

#endif
