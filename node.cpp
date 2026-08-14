#include "node.h"

#include <algorithm>

Node::Node(const std::string& id)
    : id(id), state(logicstate::floating), voltage(0.0f) {}

void Node::add_pin(Pin* pin) {
    if (pin == nullptr) {
        return;
    }

    if (std::find(pins.begin(), pins.end(), pin) == pins.end()) {
        pins.push_back(pin);
    }
}

void Node::remove_pin(Pin* pin) {
    pins.erase(std::remove(pins.begin(), pins.end(), pin), pins.end());
}

void Node::calculate_state() {
    if (pins.empty()) {
        state = logicstate::floating;
        voltage = 0.0f;
        return;
    }

    logicstate foundstate = logicstate::floating;

    for (Pin* pin : pins) {
        if (pin == nullptr) {
            continue;
        }

        logicstate pstate = pin->get_state();

        if (pstate == logicstate::floating) {
            continue;
        }

        if (foundstate == logicstate::floating) {
            foundstate = pstate;
        } else if (foundstate != pstate) {
            state = logicstate::undefined;
            voltage = 0.0f;
            return;
        }
    }

    state = foundstate;
    voltage = get_voltage();
}

float Node::get_voltage() const {
    if (state == logicstate::high) {
        return 5.0f;
    }
    if (state == logicstate::low) {
        return 0.0f;
    }

    return 0.0f;
}

std::string Node::get_id() const {
    return id;
}

void Node::set_id(const std::string& new_id) {
    id = new_id;
}

std::vector<Pin*> Node::get_pins() const {
    return pins;
}

logicstate Node::get_state() const {
    return state;
}

void Node::set_state(logicstate new_state) {
    state = new_state;
    voltage = get_voltage();
}
