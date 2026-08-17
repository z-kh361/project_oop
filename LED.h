#ifndef LED_H
#define LED_H

#include "component.h"

class LED : public Component {
private:
    std::string color_;
    bool is_on_;

public:
    // led jadid misaze
    LED(const std::string& name, const vector2d& position);

    // pin ha ro update mikone
    void update_pins() override;

    // property ha ro ba meghdar namayesh mide
    std::vector<std::pair<std::string, std::string>> get_properties() const override;

    // property ro avaz mikone
    void set_property(const std::string& key, const std::string& value) override;

    // state led ro az pin ha update mikone
    void update_state(logicstate anode_state, logicstate cathode_state);

    // mige led roshan hast ya na
    bool is_on() const;
};

#endif
