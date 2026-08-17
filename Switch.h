#ifndef SWITCH_H
#define SWITCH_H

#include "component.h"

class Switch : public Component {
private:
    bool is_closed_;

public:
    // switch jadid misaze
    Switch(const std::string& name, const vector2d& position);

    // pin ha ro update mikone
    void update_pins() override;

    // property ha ro ba meghdar namayesh mide
    std::vector<std::pair<std::string, std::string>> get_properties() const override;

    // property ro avaz mikone
    void set_property(const std::string& key, const std::string& value) override;

    // switch ro toggle mikone
    void toggle();

    // state pin ro mide
    logicstate get_pin_state(int index) const override;

    // mige switch baste hast ya na
    bool is_closed() const;
};

#endif
