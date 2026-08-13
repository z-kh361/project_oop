#include "pin.h"

Pin::Pin(const std::string& name, const vector2d& position)
    : name(name),
      position(position),
      state(logicstate::floating),
      sensitivityRadius(5.0f),
      highlighted(false) {}

bool Pin::isMouseOver(const vector2d& mousePos) const {
    return position.distanceto(mousePos) <= sensitivityRadius;
}

std::string Pin::getName() const {
    return name;
}

void Pin::setName(const std::string& newName) {
    name = newName;
}

vector2d Pin::getPosition() const {
    return position;
}

void Pin::setPosition(const vector2d& newPosition) {
    position = newPosition;
}

logicstate Pin::getState() const {
    return state;
}

void Pin::setState(logicstate newState) {
    state = newState;
}

float Pin::getSensitivityRadius() const {
    return sensitivityRadius;
}

void Pin::setSensitivityRadius(float newRadius) {
    sensitivityRadius = newRadius;
}

bool Pin::isHighlighted() const {
    return highlighted;
}

void Pin::setHighlighted(bool value) {
    highlighted = value;
}
