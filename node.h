#ifndef NODE_H
#define NODE_H

#include "pin.h"
#include "types.h"

#include <string>
#include <vector>

// Connection point between pins.
class Node {
private:
    std::string id;
    std::vector<Pin*> pins;
    logicstate state;
    float voltage;

public:
    // node jadid misaze
    explicit Node(const std::string& id);

    // pin ezafe mikone
    void add_pin(Pin* pin);
    // pin ro hazf mikone
    void remove_pin(Pin* pin);
    // state node ro hesab mikone
    void calculate_state();

    // voltage ro mide
    float get_voltage() const;

    // id ro mide
    std::string get_id() const;
    // id ro avaz mikone
    void set_id(const std::string& new_id);

    // pin ha ro mide
    std::vector<Pin*> get_pins() const;

    // state ro mide
    logicstate get_state() const;
    // state ro avaz mikone
    void set_state(logicstate new_state);
};

#endif
