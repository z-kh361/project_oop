#ifndef RESISTOR_H
#define RESISTOR_H

#include "component.h"

// Simple resistor for canvas test.
class Resistor : public Component {
private:
    float resistance_;

public:
    // resistor jadid misaze
    Resistor(const std::string& name, const vector2d& position);

    // pin ha ro update mikone
    void update_pins() override;

    // name ro baraye namayesh mide
    std::string get_display_name() const override;

    // resistance ro mide
    float get_resistance() const;

    // resistance ro avaz mikone
    void set_resistance(float resistance);
};

#endif
