#ifndef PIN_H
#define PIN_H

#include "types.h"

#include <string>

//connection point for circuit components
class Pin {
private:
    std::string name;
    vector2d position;
    logicstate state;
    float sensitivity_radius;
    bool highlighted;

public:
    // pin jadid misaze
    Pin(const std::string& name, const vector2d& position);

    // check mikone mouse ro pin hast
    bool is_mouse_over(const vector2d& mouse_pos) const;

    // name ro mide
    std::string get_name() const;
    // name ro avaz mikone
    void set_name(const std::string& new_name);

    // position ro mide
    vector2d get_position() const;
    // position ro avaz mikone
    void set_position(const vector2d& new_position);

    // state ro mide
    logicstate get_state() const;
    // state ro avaz mikone
    void set_state(logicstate new_state);

    // shoa hasasiyat ro mide
    float get_sensitivity_radius() const;
    // shoa hasasiyat ro avaz mikone
    void set_sensitivity_radius(float new_radius);

    // mige highlight hast ya na
    bool is_highlighted() const;
    // highlight ro avaz mikone
    void set_highlighted(bool value);
};

#endif
