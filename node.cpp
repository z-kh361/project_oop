#include "node.h"

#include <algorithm>

Node::Node(const std::string& id)
    : id(id), state(logicstate::floating), voltage(0.0f) {}

void Node::addpin(Pin* pin) {
    if (pin == nullptr) {
        return;
    }

    if (std::find(pins.begin(), pins.end(), pin) == pins.end()) {
        pins.push_back(pin);
    }
}

void Node::removepin(Pin* pin) {
    pins.erase(std::remove(pins.begin(), pins.end(), pin), pins.end());
}

void Node::calculatestate() {
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

        logicstate pstate = pin->getState();

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
    voltage = getvoltage();
}

float Node::getvoltage() const {
    if (state == logicstate::high) {
        return 5.0f;
    }
    if (state == logicstate::low) {
        return 0.0f;
    }

    return 0.0f;
}

std::string Node::getid() const {
    return id;
}

void Node::setid(const std::string& newid) {
    id = newid;
}

std::vector<Pin*> Node::getpins() const {
    return pins;
}

logicstate Node::getstate() const {
    return state;
}

void Node::setstate(logicstate newstate) {
    state = newstate;
    voltage = getvoltage();
}
